#ifndef __VK_VERTEX_BUFFER_H__
#define __VK_VERTEX_BUFFER_H__

#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <array>
#include <vector>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

namespace Vulpine {
  struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
  };

  const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
  };

  class VulkanBuffer {
  public:
    VulkanBuffer(VulkanContext& context);

    void Init();
    void Cleanup();

    VkBuffer buffer() { return m_Buffer; }
  private:
    VulkanContext& m_Context;
    VkBuffer m_Buffer = VK_NULL_HANDLE;
    VkDeviceMemory m_Memory = VK_NULL_HANDLE;
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  };
}


#endif
