
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Core/App.h>

namespace Vulpine
{
	void VulkanRenderer::Init()
	{
		m_Context->CreateContext();
	}

	void VulkanRenderer::Cleanup()
	{
		m_Context->Cleanup();
	}
}
