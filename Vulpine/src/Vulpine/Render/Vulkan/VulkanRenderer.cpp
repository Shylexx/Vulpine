
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Core/App.h>
#include "vppch.h"
#include <chrono>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer(Window* window)
	{
		m_Context = std::make_unique<VulkanContext>();
		m_SwapChain = std::make_unique<VulkanSwapChain>(*m_Context);
		m_DescriptorSetLayout = std::make_unique<VulkanDescriptorSetLayout>(*m_Context);
		m_Pipeline = std::make_unique<VulkanPipeline>(*m_Context, *m_SwapChain);
		m_VertexBuffer = std::make_unique<VulkanBuffer>(*m_Context);
		m_VertexStagingBuffer = std::make_unique<VulkanBuffer>(*m_Context);
		m_IndexStagingBuffer = std::make_unique<VulkanBuffer>(*m_Context);
		m_IndexBuffer = std::make_unique<VulkanBuffer>(*m_Context);
		// Uniform Buffer Creation
		m_UniformBuffers.resize(m_SwapChain->MaxFrames());
		for (size_t i = 0; i < m_SwapChain->MaxFrames(); i++) {
			m_UniformBuffers[i] = std::make_unique<VulkanBuffer>(*m_Context);
		}
		m_DescriptorPool = std::make_unique<VulkanDescriptorPool>(*m_Context);
	}

	void VulkanRenderer::Init()
	{
		m_Context->CreateContext();
		m_SwapChain->Init();
		m_DescriptorSetLayout->Init();
		m_Pipeline->Init(m_DescriptorSetLayout->layout());
		VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
		VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();
		m_VertexStagingBuffer->Init(
			vertexBufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			0,
			VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
		MapToBuffer(*m_VertexStagingBuffer, (void*)vertices.data());
		m_IndexStagingBuffer->Init(
			indexBufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			0,
			VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
		MapToBuffer(*m_IndexStagingBuffer, (void*)indices.data());
		m_IndexBuffer->Init(
			indexBufferSize,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			0,
			VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
		m_IndexStagingBuffer->CopyTo(*m_IndexBuffer, indexBufferSize);
		m_IndexStagingBuffer->Cleanup();
		m_VertexBuffer->Init(
			vertexBufferSize,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			0,
			VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
		m_VertexStagingBuffer->CopyTo(*m_VertexBuffer, vertexBufferSize);
		m_VertexStagingBuffer->Cleanup();

		VkDeviceSize uboSize = sizeof(UniformBufferObject);
		for (size_t i = 0; i < m_SwapChain->MaxFrames(); i++) {
			m_UniformBuffers[i]->Init(
				uboSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				0,
				VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
		}

		m_DescriptorPool->Init(m_SwapChain->MaxFrames());
		CreateDescriptorSets();

		CreateCommandBuffers();
	}

	void VulkanRenderer::Cleanup()
	{
		vkDeviceWaitIdle(m_Context->logicalDevice());

		m_SwapChain->Cleanup();
		m_IndexBuffer->Cleanup();
		m_VertexBuffer->Cleanup();
		for (size_t i = 0; i < m_SwapChain->MaxFrames(); i++) {
			m_UniformBuffers[i]->Cleanup();
		}
		m_DescriptorPool->Cleanup();
		m_DescriptorSetLayout->Cleanup();
		m_Pipeline->Cleanup();
		m_Context->Cleanup();
	}

	void VulkanRenderer::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(m_SwapChain->MaxFrames());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_Context->commandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

		if (vkAllocateCommandBuffers(m_Context->logicalDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Allocate Command Buffers!");
		}
	}

	void VulkanRenderer::CreateDescriptorSets()
	{
		std::vector<VkDescriptorSetLayout> layouts(m_SwapChain->MaxFrames(), m_DescriptorSetLayout->layout());
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool->pool();
		allocInfo.descriptorSetCount = static_cast<uint32_t>(m_SwapChain->MaxFrames());
		allocInfo.pSetLayouts = layouts.data();

		m_DescriptorSets.resize(m_SwapChain->MaxFrames());
		if (vkAllocateDescriptorSets(m_Context->logicalDevice(), &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS) {
			throw std::runtime_error("Failed to allocate descriptor sets!");
		}

		for (size_t i = 0; i < m_SwapChain->MaxFrames(); i++) {
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_UniformBuffers[i]->buffer();
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_DescriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrite.descriptorCount = 1;
			// We are using buffer info as our descriptor set's object (a UBO) refers to a buffer
			descriptorWrite.pBufferInfo = &bufferInfo;
			descriptorWrite.pImageInfo = nullptr;
			descriptorWrite.pTexelBufferView = nullptr;

			// Descriptor copy set can be used to copy descriptors to each other
			vkUpdateDescriptorSets(m_Context->logicalDevice(), 1, &descriptorWrite, 0, nullptr);
		}
	}

	void VulkanRenderer::DrawFrame()
	{
		// Skips Frame Draw if New Swap Chain Created
		if (!m_SwapChain->AcquireNextImage(&m_CurrentImage))
		{
			return;
		}

		UpdateUniformBuffer(m_SwapChain->CurrentFrame());

		BeginRecordCommand(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

		BeginRenderPass(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

		Render(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

		EndRenderPass(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

		EndRecordCommand(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

	}

	void VulkanRenderer::BeginRecordCommand(VkCommandBuffer commandBuffer)
	{
		vkResetCommandBuffer(commandBuffer, 0);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0;
		beginInfo.pInheritanceInfo = nullptr;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Begin Command Buffer");
		}
	}

	void VulkanRenderer::Render(VkCommandBuffer commandBuffer)
	{
		m_Pipeline->Bind(commandBuffer);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_SwapChain->extent().width);
		viewport.height = static_cast<float>(m_SwapChain->extent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0,0 };
		scissor.extent = m_SwapChain->extent();
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		// Binding Vertex Buffer
		VkBuffer vertexBuffers[] = { m_VertexBuffer->buffer() };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer->buffer(), 0, VK_INDEX_TYPE_UINT16);

		// old draw call for drawing a triangle from verts
		//vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);

		// bind the descriptor set for the current frame to the shader
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline->layout(), 0, 1, &m_DescriptorSets[m_SwapChain->CurrentFrame()], 0, nullptr);
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
	}

	void VulkanRenderer::EndRecordCommand(VkCommandBuffer commandBuffer)
	{
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Record Command Buffer");
		}

		auto swapChainStatus = m_SwapChain->SubmitCommandBuffers(&commandBuffer, &m_CurrentImage);
		if (swapChainStatus == VK_ERROR_OUT_OF_DATE_KHR || swapChainStatus == VK_SUBOPTIMAL_KHR || App::GetWindow()->wasWindowResized())
		{
			App::GetWindow()->resetWindowResizedFlag();
			m_SwapChain->RecreateSwapChain();
		}
		else if (swapChainStatus != VK_SUCCESS) {
			throw std::runtime_error("Failed to Present Image from Swap Chain");
		}
	}

	void VulkanRenderer::BeginRenderPass(VkCommandBuffer commandBuffer)
	{
		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_SwapChain->renderPass();
		renderPassInfo.framebuffer = m_SwapChain->GetFrameBuffer(m_CurrentImage);
		renderPassInfo.renderArea.offset = { 0,0 };
		renderPassInfo.renderArea.extent = m_SwapChain->extent();
		VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VulkanRenderer::EndRenderPass(VkCommandBuffer commandBuffer)
	{
		vkCmdEndRenderPass(commandBuffer);
	}

	void VulkanRenderer::MapToBuffer(VulkanBuffer& buffer, void* data) {
		// Copy the vertex data into the buffer memory
		if (buffer.map() == VK_SUCCESS) {
			//memcpy(m_MappedData, vertices.data(), (size_t)bufferInfo.size);
			buffer.WriteToBuffer(data, buffer.size());
			buffer.unmap();
		}
		else {
			std::cerr << "Could not map buffer memory" << std::endl;
		}
	}

	void VulkanRenderer::UpdateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		// Model rotation is a rotation around Z axis based on current time (will rotate on frames)
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// View Transformation is looking at the geometry from above at 45 deg angle
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.1f));
		// Perspective Projection is a 45deg vertical FOV.
		ubo.proj = glm::perspective(glm::radians(45.0f), m_SwapChain->extent().width / (float)m_SwapChain->extent().height, 0.1f, 10.0f);
		// We flip Y coord as GLM has flipped Y (for opengl)
		ubo.proj[1][1] *= -1;

		/*void* data;
		if (vmaMapMemory(m_Context->allocator(), m_UniformBuffers[currentImage]->allocation(), &data) == VK_SUCCESS){
			 memcpy(data, &ubo, sizeof(ubo));
			 vmaUnmapMemory(m_Context->allocator(), m_UniformBuffers[currentImage]->allocation());
		}
		else {
			std::cerr << "Could not map buffer memory" << std::endl;
		}*/
		if (m_UniformBuffers[currentImage]->map() == VK_SUCCESS) {
			m_UniformBuffers[currentImage]->WriteToBuffer(&ubo, sizeof(ubo));
			m_UniformBuffers[currentImage]->unmap();
		}
		else {
			std::cerr << "Could not map buffer memory" << std::endl;
		}
		
	}

}
