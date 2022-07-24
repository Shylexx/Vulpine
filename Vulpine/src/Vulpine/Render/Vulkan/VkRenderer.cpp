
#include <Vulpine/Render/Vulkan/VkRenderer.h>
#include <Vulpine/Core/App.h>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer()
	{
	}

	VulkanRenderer::~VulkanRenderer()
	{
	}
	void VulkanRenderer::Init()
	{
		m_Instance.Create();
		m_DebugMessenger.Setup();
		m_PhysicalDevice.Pick();
		m_Device.Create();
	}

	void VulkanRenderer::Cleanup()
	{
		m_Device.Cleanup();

		m_DebugMessenger.Cleanup();

		m_Instance.Cleanup();

	}
}
