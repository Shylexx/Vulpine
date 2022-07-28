#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Render/Vulkan/VulkanContext.h>
#include <Vulpine/Render/Vulkan/VulkanSwapChain.h>
#include <Vulpine/Core/Window.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Vulpine
{

class VulkanRenderer
{
public:
	VulkanRenderer(Window *window);
	~VulkanRenderer() = default;

	void Init();
	void Cleanup();

private:
	std::unique_ptr<VulkanContext> m_Context;
  std::unique_ptr<VulkanSwapChain> m_SwapChain;
  std::unique_ptr<VulkanPipeline> m_Pipeline;
};

}
#endif
