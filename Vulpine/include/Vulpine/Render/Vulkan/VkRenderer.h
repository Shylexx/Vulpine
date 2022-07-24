#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VkDebugMessenger.h>
#include <Vulpine/Render/Vulkan/VkInstance.h>
#include <Vulpine/Render/Vulkan/VkLogicalDevice.h>
#include <Vulpine/Render/Vulkan/VkPhysicalDevice.h>


namespace Vulpine
{

	class VulkanRenderer
	{
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Init();
		void Cleanup();

	private:
		VulkanLogicalDevice m_Device;
		VulkanInstance m_Instance;
		VulkanDebugMessenger m_DebugMessenger;
		VulkanPhysicalDevice m_PhysicalDevice;

	};

}
#endif
