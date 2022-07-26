#ifndef __VK_INSTANCE_H__
#define __VK_INSTANCE_H__

#include <Vulpine/Render/Vulkan/VulkanDebugMessenger.h>

#include <vector>
#include <vulkan/vulkan.h>

namespace Vulpine
{
class VulkanInstance
{
public:
	void Create();
	void Cleanup();
	VkInstance& instance() { return m_Instance; }
private:

	const std::vector<const char *> m_ValidationLayers = {
				"VK_LAYER_KHRONOS_validation"
	};


	VkInstance m_Instance;

	std::unique_ptr<VulkanDebugMessenger> m_DebugMessenger;



	std::vector<const char*> getReqExtensions();
	bool CheckValidationLayerSupport();
};

}
#endif
