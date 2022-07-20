#ifndef __VP_DEVICE_H__
#define __VP_DEVICE_H__

#include <vulkan/vulkan.h>

namespace Vulpine
{
	class VulpineDevice
	{
		public:
			VulpineDevice();
			~VulpineDevice();
			VkDevice device() { return m_VkDevice; }
		private:
			VkDevice m_VkDevice;
			VkPhysicalDevice m_VkPhysicalDevice;
			VkInstance m_VkInstance;
	};
}

#endif
