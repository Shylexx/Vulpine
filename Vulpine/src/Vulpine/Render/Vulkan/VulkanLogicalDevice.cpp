
#include <Vulpine/Render/Vulkan/VulkanLogicalDevice.h>
#include <Vulpine/Render/Vulkan/VulkanPhysicalDevice.h>
#include <Vulpine/Core/App.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <vulkan/vulkan.h>


// TO DO:
// ADD VALIDATION LAYER AND DEBUG SUPPORT
// GET AVAILABLE EXTENSIONS CORRECTLY
namespace Vulpine
{
	void VulkanLogicalDevice::Create(VkPhysicalDevice physicalDevice)
	{
		// THIS CALL SEGFAULTS
		QueueFamilyIndices indices = VulkanPhysicalDevice::FindAvailableQueueFamilies(physicalDevice);

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

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_VkDevice) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Logical Device!");
		}

		vkGetDeviceQueue(m_VkDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
	}

	void VulkanLogicalDevice::Cleanup()
	{
		vkDestroyDevice(m_VkDevice, nullptr);
	}

	// Not currently working
	QueueFamilyIndices VulkanLogicalDevice::CreateQueueIndices()
	{
		QueueFamilyIndices indices;/*

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice.PhysicalDevice(), &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice.PhysicalDevice(), &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}

			i++;
		}*/

		return indices;
	}

}
