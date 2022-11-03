#include "Vulpine/Render/Vulkan/VulkanBuffer.h"
#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <cstring>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <iostream>

namespace Vulpine {

	VkVertexInputBindingDescription Vertex::getBindingDescription() {
		// Specifies the number of bytes between vertex data entries
		// and whether to move to next entry after vertex or after instance
		VkVertexInputBindingDescription bindingDescription{};
		// Index of the binding in the array of bindings
		bindingDescription.binding = 0;
		// Bytes between entries (Vertexes)
		bindingDescription.stride = sizeof(Vertex);
		// Vertex mode is move between vertexes (not instances)
		// Instance mode is for instanced rendering
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		// Only one binding as vertex data in one array

		return bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 2> Vertex::getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		// 2 channels
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		// Color attribute
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		// 3 color channels (RGB)
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}

	VulkanBuffer::VulkanBuffer(VulkanContext& context)
		: m_Context(context)
	{
	}

	void VulkanBuffer::Init(VkDeviceSize size, VkBufferUsageFlags usages, VkMemoryPropertyFlags requiredFlags, VkMemoryPropertyFlags preferredFlags, VmaAllocationCreateFlags allocFlags) {
		VkBufferCreateInfo bufferInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
		// Size buffer to the size of the vertex we are sending to it
		bufferInfo.size = size;
		// Purposes the buffer will be used for 
		bufferInfo.usage = usages;
		// Only graphics queue will use
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VmaAllocationCreateInfo allocInfo{};
		allocInfo.usage = VMA_MEMORY_USAGE_AUTO;
		allocInfo.flags = allocFlags;
		allocInfo.requiredFlags = requiredFlags;
		allocInfo.preferredFlags = preferredFlags;

		m_BufferSize = size;

		if (vmaCreateBuffer(m_Context.allocator(), &bufferInfo, &allocInfo, &m_Buffer, &m_Allocation, nullptr) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Create Buffer!");
		}
	}

	void VulkanBuffer::Cleanup() {
		vmaDestroyBuffer(m_Context.allocator(), m_Buffer, m_Allocation);
	}

	void VulkanBuffer::CopyTo(VulkanBuffer& dstBuffer, VkDeviceSize size) {
		VkCommandBufferAllocateInfo bufAllocInfo{};
		bufAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		bufAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		bufAllocInfo.commandPool = m_Context.commandPool();
		bufAllocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(m_Context.logicalDevice(), &bufAllocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0;
		copyRegion.dstOffset = 0;
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, m_Buffer, dstBuffer.buffer(), 1, &copyRegion);
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_Context.graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_Context.graphicsQueue());

		vkFreeCommandBuffers(m_Context.logicalDevice(), m_Context.commandPool(), 1, &commandBuffer);
	}

	VkResult VulkanBuffer::map(VkDeviceSize size, VkDeviceSize offset) {
		return vmaMapMemory(m_Context.allocator(), m_Allocation, &m_MappedData);
	}

	void VulkanBuffer::unmap() {
		if (m_MappedData) {
			vmaUnmapMemory(m_Context.allocator(), m_Allocation);
			m_MappedData = nullptr;
		}
	}

	void VulkanBuffer::WriteToBuffer(void* data, VkDeviceSize size, VkDeviceSize offset) {
		if (!m_MappedData) {
			std::cerr << "Could not Write to buffer with no mapped data!" << std::endl;
			return;
		}

		if (size == VK_WHOLE_SIZE) {
			memcpy(m_MappedData, data, m_BufferSize);
		}
		else {
			char* memOffset = (char*)m_MappedData;
			memOffset += offset;
			memcpy(memOffset, data, size);
		}

	}

	uint32_t VulkanBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(m_Context.physicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		throw std::runtime_error("Failed to find suitable memory type for buffer!");
	}
}
