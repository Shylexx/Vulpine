
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Core/App.h>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer()
	{
		m_Context = std::make_unique<VulkanContext>();
	}

	void VulkanRenderer::Init()
	{
		m_Context->CreateContext();
	}

	void VulkanRenderer::Cleanup()
	{
		m_Context->Cleanup();
	}
}
