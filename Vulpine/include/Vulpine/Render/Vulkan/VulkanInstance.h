#ifndef __VK_INSTANCE_H__
#define __VK_INSTANCE_H__

#include <vector>
#include <vulkan/vulkan.h>

namespace Vulpine
{
class VulkanInstance
{
public:
	void Create();
	void Cleanup();
	VkInstance instance() { return m_Instance; }
private:

	const std::vector<const char *> m_ValidationLayers = {
				"VK_LAYER_KHRONOS_validation"
	};


	VkInstance m_Instance;

	std::vector<const char*> getReqExtensions();
	bool CheckValidationLayerSupport();
};

}
#endif
