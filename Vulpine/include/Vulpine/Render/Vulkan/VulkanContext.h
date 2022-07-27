#ifndef __VK_CONTEXT_H__
#define __VK_CONTEXT_H__

#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <vulkan/vulkan.h>

#include <vector>

namespace Vulpine
{
  class VulkanContext
  {
  public:
      VulkanContext() = default;
      ~VulkanContext() = default;

    void CreateContext();
    void Cleanup();
  private:
    const std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

    VkDevice m_LogicalDevice = VK_NULL_HANDLE;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkInstance m_Instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

    VkQueue m_GraphicsQueue;

    QueueFamilyIndices FindAvailableQueueFamilies(VkPhysicalDevice physicalDevice);
    bool IsPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice);

    void CreateInstance();
    void SetupDebugMessenger();
    void PickPhysicalDevice();
    void CreateLogicalDevice();

    bool m_EnableValidationLayers = true;

    void PopulateDebugMessengerCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

    bool CheckValidationLayerSupport();
    std::vector<const char *> GetRequiredExtensions();

    

  };
}

#endif
