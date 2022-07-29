
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Core/App.h>
#include <stdexcept>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer(Window *window)
	{
		m_Context = std::make_unique<VulkanContext>(window);
    m_SwapChain = std::make_unique<VulkanSwapChain>(*m_Context);
    m_Pipeline = std::make_unique<VulkanPipeline>(*m_Context, *m_SwapChain);
	}

	void VulkanRenderer::Init()
	{
		m_Context->CreateContext();
    m_SwapChain->Init();
    m_Pipeline->Init();
	}

	void VulkanRenderer::Cleanup()
	{
    vkDeviceWaitIdle(m_Context->logicalDevice());

    m_SwapChain->Cleanup();
		m_Context->Cleanup();
    m_Pipeline->Cleanup();
	}

  void VulkanRenderer::CreateCommandBuffer()
  {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_Context->commandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if(vkAllocateCommandBuffers(m_Context->logicalDevice(), &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Allocate Command Buffers!");
    }
  }

  void VulkanRenderer::DrawFrame()
  {
    m_SwapChain->AcquireNextImage(&m_ImageIndex);

    BeginFrame();

    BeginRenderPass(m_CommandBuffer);

    Render();

    EndRenderPass(m_CommandBuffer);

    EndFrame();




  }

  VkCommandBuffer VulkanRenderer::BeginFrame()
  {
    vkResetCommandBuffer(m_CommandBuffer, 0);

    VkCommandBufferBeginInfo beginInfo {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    if(vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Begin Command Buffer");
    }

    return m_CommandBuffer;
  }

  void VulkanRenderer::Render()
  {
    m_Pipeline->Bind(m_CommandBuffer);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_SwapChain->extent().width);
    viewport.height = static_cast<float>(m_SwapChain->extent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(m_CommandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0,0};
    scissor.extent = m_SwapChain->extent();
    vkCmdSetScissor(m_CommandBuffer, 0, 1, &scissor);

    vkCmdDraw(m_CommandBuffer, 3, 1, 0, 0);
  }

  void VulkanRenderer::EndFrame()
  {
    if(vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Record Command Buffer");
    }

    auto result = m_SwapChain->SubmitCommandBuffers(&m_CommandBuffer, &m_ImageIndex);
    if(result != VK_SUCCESS) {
      throw std::runtime_error("Failed to Present Image!");
    }
  }

  void VulkanRenderer::BeginRenderPass(VkCommandBuffer commandBuffer)
  {
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_SwapChain->renderPass();
    renderPassInfo.framebuffer = m_SwapChain->GetFrameBuffer(m_ImageIndex);
    renderPassInfo.renderArea.offset = {0,0};
    renderPassInfo.renderArea.extent = m_SwapChain->extent();
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  }

  void VulkanRenderer::EndRenderPass(VkCommandBuffer commandBuffer)
  {
    vkCmdEndRenderPass(m_CommandBuffer);
  }
}
