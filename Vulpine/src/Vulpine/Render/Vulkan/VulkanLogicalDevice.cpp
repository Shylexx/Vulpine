
#include <Vulpine/Render/Vulkan/VulkanLogicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>
#include <Vulpine/Core/App.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vulkan/vulkan.h>


// TO DO:
// ADD VALIDATION LAYER AND DEBUG SUPPORT
// GET AVAILABLE EXTENSIONS CORRECTLY
namespace Vulpine
{
	void VulkanLogicalDevice::Create()
	{
		QueueFamilyIndices indices = VulkanPhysicalDevice::FindAvailableQueueFamilies(m_PhysicalDevice.physicalDevice());

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;

		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;
		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(m_PhysicalDevice.physicalDevice(), &createInfo, nullptr, &m_VkDevice) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Logical Device!");
		}

		vkGetDeviceQueue(m_VkDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
	}

		void VulkanLogicalDevice::Cleanup()
	{
		vkDestroyDevice(m_VkDevice, nullptr);
	}

}
