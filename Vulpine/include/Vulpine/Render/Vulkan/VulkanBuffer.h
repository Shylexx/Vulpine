#ifndef __VK_VERTEX_BUFFER_H__
#define __VK_VERTEX_BUFFER_H__

#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <vk_mem_alloc.h>
#include "vppch.h"
#include <glm/glm.hpp>

namespace Vulpine {
  struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
  };

  const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
  };

  const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
  };

  class VulkanBuffer {
  public:
    VulkanBuffer(VulkanContext& context);

    void Init(VkDeviceSize size, VkBufferUsageFlags usages, VkMemoryPropertyFlags requiredMemProps, VkMemoryPropertyFlags preferredMemProps = 0, VmaAllocationCreateFlags allocFlags = 0);
    void CopyTo(VulkanBuffer& dstBuffer, VkDeviceSize size = VK_WHOLE_SIZE);
    void Cleanup();

    VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
    void unmap();

    VkBuffer buffer() { return m_Buffer; }
    VkDeviceSize size() { return m_BufferSize; }
    void* mappedData() { return m_MappedData; }

    void WriteToBuffer(void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
  private:
    VulkanContext& m_Context;
    
    VkBuffer m_Buffer = VK_NULL_HANDLE;
    VkDeviceSize m_BufferSize = 0;
    VmaAllocation m_Allocation = VK_NULL_HANDLE;
    
    void* m_MappedData = nullptr;

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  };
}


#endif
