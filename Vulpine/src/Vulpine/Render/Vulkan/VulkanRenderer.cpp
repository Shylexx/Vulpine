
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Core/App.h>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer(Window *window)
	{
		m_Context = std::make_unique<VulkanContext>(window);
    m_SwapChain = std::make_unique<VulkanSwapChain>(*m_Context);
    m_Pipeline = std::make_unique<VulkanPipeline>(*m_Context, *m_SwapChain);
	}

	void VulkanRenderer::Init()
	{
		m_Context->CreateContext();
    m_SwapChain->Init();
    m_Pipeline->Init();
	}

	void VulkanRenderer::Cleanup()
	{
    m_SwapChain->Cleanup();
		m_Context->Cleanup();
	}
}
