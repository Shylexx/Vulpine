#ifndef __VK_PHYSICAL_DEVICE_H__
#define __VK_PHYSICAL_DEVICE_H__

#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <vulkan/vulkan.h>

namespace Vulpine
{
	class VulkanPhysicalDevice
	{
	public:
		void Pick(VkInstance instance);

		VkPhysicalDevice physicalDevice() { return m_VkPhysicalDevice; }
		static bool IsDeviceSuitable(VkPhysicalDevice device);
		static QueueFamilyIndices FindAvailableQueueFamilies(VkPhysicalDevice device);
		QueueFamilyIndices GetQueueFamilies();
	private:
		VkPhysicalDevice m_VkPhysicalDevice;

		
	};
}

#endif
