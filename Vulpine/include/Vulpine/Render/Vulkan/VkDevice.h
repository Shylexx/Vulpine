#ifndef __VP_DEVICE_H__
#define __VP_DEVICE_H__

#include <vulkan/vulkan.h>
#include <optional>

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

	class VulpineDevice
	{
		public:
			VulpineDevice();
			~VulpineDevice();
			VkDevice device() { return m_VkDevice; }
		private:
			void CreateVkInstance();
			void SetupDebugMessenger();
			void PickPhysicalDevice();
			void CreateLogicalDevice();

			// Helper functions
			void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

			VkDevice m_VkDevice;
			VkPhysicalDevice m_VkPhysicalDevice;
			VkInstance m_VkInstance;
			VkDebugUtilsMessengerEXT m_DebugMessenger;
			
			VkQueue m_GraphicsQueue;
	};
}

#endif
