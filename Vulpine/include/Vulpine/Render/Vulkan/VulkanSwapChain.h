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

    VkSwapchainKHR swapChain() { return m_SwapChain; }
    VkExtent2D extent() { return m_SwapChainExtent; }
    VkFormat format() { return m_SwapChainImageFormat; }
    std::vector<VkImage> images() { return m_SwapChainImages; }
    std::vector<VkImageView> imageViews() { return m_SwapChainImageViews; }
  private:
    VkSwapchainKHR m_SwapChain;
    VkRenderPass m_RenderPass;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;
    std::vector<VkImageView> m_SwapChainImageViews;

    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VulkanContext& m_Context;
  };
}

#endif
