#ifndef __VK_PIPELINE_H__
#define __VK_PIPELINE_H__

#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include "Vulpine/Render/Vulkan/VulkanSwapChain.h"
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

namespace Vulpine
{
  class VulkanPipeline
  {
  public:
    VulkanPipeline(VulkanContext& context, VulkanSwapChain& swapChain);
    ~VulkanPipeline() = default;

    void Init();
    void Cleanup();
  private:

    VulkanContext& m_Context;
    VulkanSwapChain& m_SwapChain;

    VkPipeline m_Pipeline;
    VkPipelineLayout m_Layout;

    void CreatePipeline();

    std::vector<char> ReadFile(const std::string& filepath);

    VkShaderModule CreateShaderModule(const std::vector<char>& code);
  };
}

#endif
