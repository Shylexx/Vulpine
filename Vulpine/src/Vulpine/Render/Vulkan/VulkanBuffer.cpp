#include "Vulpine/Render/Vulkan/VulkanBuffer.h"
#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <cstring>
#include <vulkan/vulkan.h>
#include <stdexcept>

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

  void VulkanBuffer::Init() {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    // Size buffer to the size of the vertex we are sending to it
    bufferInfo.size = sizeof(vertices[0]) * vertices.size();
    // Purposes the buffer will be used for (vertex buffer)
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    // Only graphics queue will use
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(m_Context.logicalDevice(), &bufferInfo, nullptr, &m_Buffer) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Create Buffer!");
    }

    // Querying Memory Requirements
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_Context.logicalDevice(), m_Buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(m_Context.logicalDevice(), &allocInfo, nullptr, &m_Memory) != VK_SUCCESS) {
      throw std::runtime_error("Failed to allocate buffer memory!");
    }

    vkBindBufferMemory(m_Context.logicalDevice(), m_Buffer, m_Memory, 0);

    // Map buffer memory into cpu accessible memory
    // Accesses a region of memory resource (0 is offset, bufferInfo.size is size)
    void* data;
    vkMapMemory(m_Context.logicalDevice(), m_Memory, 0, bufferInfo.size, 0, &data);
    // Copy the vertex data into the buffer memory
    memcpy(data, vertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(m_Context.logicalDevice(), m_Memory);
  }

  void VulkanBuffer::Cleanup() {
    vkDestroyBuffer(m_Context.logicalDevice(), m_Buffer, nullptr);
    vkFreeMemory(m_Context.logicalDevice(), m_Memory, nullptr);
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
