#ifndef __VP_DEVICE_H__
#define __VP_DEVICE_H__

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

namespace Vulpine
{

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value();
		}
	};

	class VulkanLogicalDevice
	{
		public:
			VulkanLogicalDevice();
			~VulkanLogicalDevice();
			VkDevice device() { return m_VkDevice; }
			void Cleanup();
		private:
			void CreateVkInstance();
			void SetupDebugMessenger();
			void PickPhysicalDevice();
			void CreateLogicalDevice();

			// Helper functions
			void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
			std::vector<const char *> getReqExtensions();
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
			bool CheckValidationLayerSupport();

			//Debug Util Messenger Creation and Cleanup
			VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
			void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);

			VkDevice m_VkDevice;
			VkPhysicalDevice m_VkPhysicalDevice;
			VkInstance m_VkInstance;
			VkDebugUtilsMessengerEXT m_DebugMessenger;

			const std::vector<const char *> validationLayers = {
				"VK_LAYER_KHRONOS_validation"
			};
			
			VkQueue m_GraphicsQueue;
	};
}

#endif
