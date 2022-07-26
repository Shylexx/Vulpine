#ifndef __VK_PHYSICAL_DEVICE_H__
#define __VK_PHYSICAL_DEVICE_H__

#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <vulkan/vulkan.h>
#include <Vulpine/Render/Vulkan/VulkanInstance.h>

namespace Vulpine
{
	class VulkanPhysicalDevice
	{
	public:
		void Pick(VkInstance instance);

		static bool IsDeviceSuitable(VkPhysicalDevice &device);
		static QueueFamilyIndices FindAvailableQueueFamilies(VkPhysicalDevice &device);

		VkPhysicalDevice& PhysicalDevice() { return m_VkPhysicalDevice; }
	private:

		VkPhysicalDevice m_VkPhysicalDevice = VK_NULL_HANDLE;


		//const VulkanInstance& m_Instance;

		
	};
}

#endif
