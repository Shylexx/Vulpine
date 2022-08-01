#ifndef __VK_CONTEXT_H__
#define __VK_CONTEXT_H__

#include <Vulpine/Core/Window.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <vulkan/vulkan_core.h>

namespace Vulpine
{

  struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };

  struct QueueFamilyIndices
  {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
  };

  class VulkanContext
  {
  public:
      VulkanContext();
      ~VulkanContext() = default;

    void CreateContext();
    void Cleanup();

    VkDevice logicalDevice() { return m_LogicalDevice; }
    VkSurfaceKHR surface() { return m_Surface; }
    VkQueue graphicsQueue() { return m_GraphicsQueue; }
    VkQueue presentQueue() { return m_PresentQueue; }
    VkCommandPool commandPool() { return m_CommandPool; }

    SwapChainSupportDetails PhysicalDeviceSwapChainSupport();
    QueueFamilyIndices PhysicalDeviceQueueFamilies();
  private:


    VkDevice m_LogicalDevice = VK_NULL_HANDLE;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkInstance m_Instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
    VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
    VkCommandPool m_CommandPool = VK_NULL_HANDLE;

    VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
    VkQueue m_PresentQueue = VK_NULL_HANDLE;

    QueueFamilyIndices FindAvailableQueueFamilies(VkPhysicalDevice physicalDevice);
    bool IsPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice);

    void CreateInstance();
    void SetupDebugMessenger();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateCommandPool();

    bool m_EnableValidationLayers = true;

    void PopulateDebugMessengerCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

    bool CheckValidationLayerSupport();
    bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice);
    std::vector<const char *> GetRequiredExtensions();

    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice physicalDevice);

    const std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

  };
}

#endif
