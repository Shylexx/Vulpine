#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanContext.h>

namespace Vulpine
{

class VulkanRenderer
{
public:
	void Init();
	void Cleanup();

private:
	std::unique_ptr<VulkanContext> m_Context;

};

}
#endif
