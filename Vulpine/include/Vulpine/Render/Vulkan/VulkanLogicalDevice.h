#ifndef __VP_DEVICE_H__
#define __VP_DEVICE_H__

#include "Vulpine/Render/Vulkan/VulkanDebugMessenger.h"
#include <vulkan/vulkan.h>
#include <optional>
#include <vector>
#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanInstance.h>

namespace Vulpine
{

	class VulkanLogicalDevice
	{
		public:
			VkDevice device() { return m_VkDevice; }
			void Cleanup();
			void Create();
		private:
			
			// Helper functions
			void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
			std::vector<const char *> getReqExtensions();
			bool CheckValidationLayerSupport();

			

			VkDevice m_VkDevice;
			VulkanPhysicalDevice m_PhysicalDevice;
			VulkanInstance m_Instance;
			VulkanDebugMessenger m_DebugMessenger;

			
			
			VkQueue m_GraphicsQueue;
	};
}

#endif
