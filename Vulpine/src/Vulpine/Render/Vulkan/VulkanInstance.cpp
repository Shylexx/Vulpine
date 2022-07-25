#include <Vulpine/Render/Vulkan/VulkanInstance.h>
#include <Vulpine/Render/Vulkan/VulkanDebugMessenger.h>
#include <Vulpine/Core/App.h>
#include <cstring>

namespace Vulpine
{
    void VulkanInstance::Create()
    {
        if(App::GetInstance().debugMode() && !CheckValidationLayerSupport())
		{
			std::cout << "Validation Layers Available: " << CheckValidationLayerSupport() << std::endl;
			throw std::runtime_error("Cannot use Debug: Validation Layers not Available!");
		}

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulpine Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Vulpine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.apiVersion = VK_API_VERSION_1_3;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getReqExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

		if(App::GetInstance().debugMode())
		{
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
		createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
		VulkanDebugMessenger::PopulateDebugMessengerCreateInfoStruct(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
		} else {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
		}
		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan Instance");
		}
    }

	void VulkanInstance::Cleanup()
	{
		vkDestroyInstance(m_Instance, nullptr);
	}

    std::vector<const char*> VulkanInstance::getReqExtensions()
	{
		uint32_t glfwExtensionCount = 0;

		const char **glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if(App::GetInstance().debugMode())
		{
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return extensions;
	}

    bool VulkanInstance::CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : m_ValidationLayers)
        {
            bool layerFound = false;
            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }
}