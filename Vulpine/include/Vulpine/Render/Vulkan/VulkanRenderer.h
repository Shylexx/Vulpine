#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanDebugMessenger.h>
#include <Vulpine/Render/Vulkan/VulkanInstance.h>
#include <Vulpine/Render/Vulkan/VulkanLogicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>


namespace Vulpine
{

struct VLogicalDevice
{
	VLogicalDevice();
	VkDevice device;
	void Cleanup();
	void Create(VkPhysicalDevice physicalDevice);

	VkDevice m_VkDevice = VK_NULL_HANDLE;

	QueueFamilyIndices CreateQueueIndices();

	VkQueue m_GraphicsQueue;
};

struct VPhysicalDevice
{
	VPhysicalDevice();
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkInstance instance = VK_NULL_HANDLE;
	bool IsDeviceSuitable(VkPhysicalDevice& device);
	QueueFamilyIndices FindAvailableQueueFamilies(VkPhysicalDevice& device);

	std::vector<const char*> getReqExtensions();
	bool CheckValidationLayerSupport();
};

class VulkanRenderer
{
public:
	void Init();
	void Cleanup();

private:
	std::unique_ptr<VLogicalDevice> m_Device;
	std::unique_ptr<VPhysicalDevice> m_PhysicalDevice;
	VkDebugUtilsMessengerEXT m_DebugMessenger;

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

};

}
#endif
