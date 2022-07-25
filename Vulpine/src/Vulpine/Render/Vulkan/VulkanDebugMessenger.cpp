#include <Vulpine/Render/Vulkan/VulkanDebugMessenger.h>

namespace Vulpine
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
		void *pUserData)
	{
		std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

    void VulkanDebugMessenger::Setup(VkInstance instance)
    {
    	VkDebugUtilsMessengerCreateInfoEXT createInfo;
		PopulateDebugMessengerCreateInfoStruct(createInfo);

		if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
			throw std::runtime_error("Failed to Create Debug Utils Messenger");
	}

	void VulkanDebugMessenger::Cleanup(VkInstance instance)
	{
		DestroyDebugUtilsMessengerEXT(instance, m_DebugMessenger, nullptr);
	}

	//Debug Util Messenger Creation and Cleanup
	VkResult VulkanDebugMessenger::CreateDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
			const VkAllocationCallbacks *pAllocator,
			VkDebugUtilsMessengerEXT *pDebugMessenger
			)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if(func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else 
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanDebugMessenger::DestroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks *pAllocator
			)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if(func != nullptr)
		{
			func(instance, debugMessenger, pAllocator);
		}
	}

	void VulkanDebugMessenger::PopulateDebugMessengerCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
	{
		createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
	}
	
}

