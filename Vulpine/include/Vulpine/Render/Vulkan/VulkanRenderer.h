#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanDebugMessenger.h>
#include <Vulpine/Render/Vulkan/VulkanInstance.h>
#include <Vulpine/Render/Vulkan/VulkanLogicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>


namespace Vulpine
{

	class VulkanRenderer
	{
	public:
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
