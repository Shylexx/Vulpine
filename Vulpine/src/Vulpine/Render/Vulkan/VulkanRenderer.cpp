
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Core/App.h>

namespace Vulpine
{
	void VulkanRenderer::Init()
	{
		m_Instance->Create();
		//m_DebugMessenger->Setup(m_Instance.instance());
		m_PhysicalDevice->Pick(m_Instance->instance());
		m_Device->Create(m_PhysicalDevice->PhysicalDevice());
	}

	void VulkanRenderer::Cleanup()
	{
		m_Device->Cleanup();

		/*if(App::GetInstance().debugMode())
		{
			m_DebugMessenger.Cleanup(m_Instance.instance());
		}*/

		m_Instance->Cleanup();
	}
}
