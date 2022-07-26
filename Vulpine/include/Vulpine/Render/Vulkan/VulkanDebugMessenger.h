#ifndef __VK_DEBUG_MESSENGER_H__
#define __VK_DEBUG_MESSENGER_H__


#include <vulkan/vulkan.h>
namespace Vulpine
{
	class VulkanDebugMessenger
	{
	public:
		void Setup(VkInstance instance);
		void Cleanup(VkInstance instance);

		static void PopulateDebugMessengerCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

		VkDebugUtilsMessengerEXT& debugMessenger() { return m_DebugMessenger; }

	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
		//Debug Util Messenger Creation and Cleanup
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

	};
}
#endif
