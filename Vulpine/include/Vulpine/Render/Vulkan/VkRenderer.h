#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VkDevice.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>


namespace Vulpine
{

class VulkanRenderer
{
public:
	VulkanRenderer();
	~VulkanRenderer();

private:
	VulpineDevice m_Device;
};

}
#endif
