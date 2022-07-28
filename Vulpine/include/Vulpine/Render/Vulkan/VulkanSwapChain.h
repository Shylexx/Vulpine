#ifndef __VK_SWAP_CHAIN_H__
#define __VK_SWAP_CHAIN_H__

#include <Vulpine/Render/Vulkan/VulkanContext.h>
#include <vector>
#include <vulkan/vulkan.h>

namespace Vulpine
{
  class VulkanSwapChain
  {
  public:
    VulkanSwapChain(VulkanContext& contextRef);
    ~VulkanSwapChain() = default;
    void Init();
    void Cleanup();
  private:
    VkSwapchainKHR m_SwapChain;
    VulkanContext& m_Context;

    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;

    void CreateSwapChain();
    
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  };
}

#endif
