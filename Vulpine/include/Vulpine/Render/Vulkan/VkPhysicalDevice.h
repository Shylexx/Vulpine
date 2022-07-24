#ifndef __VK_PHYSICAL_DEVICE_H__
#define __VK_PHYSICAL_DEVICE_H__

#include <vulkan/vulkan.h>

namespace Vulpine
{
	class VulkanPhysicalDevice
	{
	public:
		void Pick();

		VkPhysicalDevice physicalDevice() { return m_VkPhysicalDevice(); }
	private:
		VkPhysicalDevice m_VkPhysicalDevice();
	};
}

#endif
