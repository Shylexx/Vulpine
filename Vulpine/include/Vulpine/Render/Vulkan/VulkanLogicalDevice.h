#ifndef __VP_DEVICE_H__
#define __VP_DEVICE_H__

#include "Vulpine/Render/Vulkan/VulkanDebugMessenger.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanInstance.h>

namespace Vulpine
{

	class VulkanLogicalDevice
	{
		public:
			VulkanLogicalDevice();

			VkDevice& device() { return m_VkDevice; }
			void Cleanup();
			void Create(VkPhysicalDevice physicalDevice);
			
		private:
			//VulkanPhysicalDevice& m_PhysicalDevice;
			//VulkanInstance& m_Instance;

			VkDevice m_VkDevice = VK_NULL_HANDLE;

			QueueFamilyIndices CreateQueueIndices();
			
			VkQueue m_GraphicsQueue;
	};
}

#endif
