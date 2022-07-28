#ifndef __VK_PIPELINE_H__
#define __VK_PIPELINE_H__

#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

namespace Vulpine
{
  class VulkanPipeline
  {
  public:
    VulkanPipeline(VulkanContext& context);
    ~VulkanPipeline() = default;

    void Init();
    void Cleanup();
  private:

    VulkanContext& m_Context;

    VkPipeline m_Pipeline;

    void CreatePipeline();

    std::vector<char> ReadFile(const std::string& filepath);

    VkShaderModule CreateShaderModule(const std::vector<char>& code);
  };
}

#endif
