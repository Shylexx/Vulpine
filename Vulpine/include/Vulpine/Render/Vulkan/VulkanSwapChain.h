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
    VkRenderPass renderPass() { return m_RenderPass; }
    std::vector<VkImage> images() { return m_SwapChainImages; }
    std::vector<VkImageView> imageViews() { return m_SwapChainImageViews; }
    std::vector<VkFramebuffer> frameBuffers() { return m_SwapChainFrameBuffers; }
    VkFramebuffer GetFrameBuffer(int index) { return m_SwapChainFrameBuffers[index]; }
    uint32_t CurrentFrame() { return m_CurrentFrame; }

    std::vector<VkFence> InFlightFences() { return m_InFlightFences; }

    void AcquireNextImage(uint32_t *imageIndex);
    VkResult SubmitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);


    int MaxFrames() { return MAX_FRAMES_IN_FLIGHT; }
    
  private:
    VkSwapchainKHR m_SwapChain;
    VkRenderPass m_RenderPass;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;
    std::vector<VkImageView> m_SwapChainImageViews;
    std::vector<VkFramebuffer> m_SwapChainFrameBuffers;

    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateFrameBuffers();
    void CreateSyncObjects();
    
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    std::vector<VkSemaphore> m_ImageAvailableSemaphores;
    std::vector<VkSemaphore> m_RenderFinishedSemaphores;
    std::vector<VkFence> m_InFlightFences;

    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t m_CurrentFrame{ 0 };

    VulkanContext& m_Context;
  };
}

#endif
