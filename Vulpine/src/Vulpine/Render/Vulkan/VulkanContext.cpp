#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <Vulpine/Render/Vulkan/VulkanQueueFamilyIndices.h>
#include <Vulpine/Render/Vulkan/VulkanContext.h>
#include <Vulpine/Core/App.h>

#include <stdexcept>
#include <cstring>
#include <iostream>

namespace Vulpine
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    )
    {
        //std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
        std::cerr << "Validation Layer Message" << std::endl;
        return VK_FALSE;
    }

    VulkanContext::VulkanContext(Window* window)
        : m_Window(window)
    {
    }

  void VulkanContext::CreateContext()
  {
    std::cout << "Create Instance" << std::endl;
    CreateInstance();
    std::cout << "Setup Debug Messenger" << std::endl;
    SetupDebugMessenger();
    std::cout << "Create Surface" << std::endl;
    CreateSurface();
    std::cout << "Pick Physical Device" << std::endl;
    PickPhysicalDevice();
    std::cout << "Create Logical Device" << std::endl;
    CreateLogicalDevice();
  }

  void VulkanContext::Cleanup()
  {
    vkDestroyDevice(m_LogicalDevice, nullptr);

    if(m_EnableValidationLayers)
    {
      DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);

    vkDestroyInstance(m_Instance, nullptr);

    std::cout << "Vulkan Context Cleaned Up" << std::endl;
  }

  void VulkanContext::CreateInstance()
  {
    if(!CheckValidationLayerSupport())
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

		VkInstanceCreateInfo createInfo= {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = GetRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		if(true)
		{
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		    createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
		    createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

		    PopulateDebugMessengerCreateInfoStruct(debugCreateInfo);
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

  void VulkanContext::SetupDebugMessenger()
  {
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    PopulateDebugMessengerCreateInfoStruct(createInfo);

    if(CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
      throw std::runtime_error("Failed to Create Debug Utils Messenger");
  }

  void VulkanContext::PickPhysicalDevice()
  {
    uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to find GPU with Vulkan Support");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

		for (auto device : devices)
		{
            
			if (IsPhysicalDeviceSuitable(device))
			{
				m_PhysicalDevice = device;
				break;
			}
		}

		if (m_PhysicalDevice == VK_NULL_HANDLE)
		{
            std::cout << "Failed to find GPU" << std::endl;
			throw std::runtime_error("Failed to find a suitable GPU!");
		}

  }

  void VulkanContext::CreateLogicalDevice()
  {
    // THIS CALL SEGFAULTS
		QueueFamilyIndices indices = FindAvailableQueueFamilies(m_PhysicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

        if (App::GetInstance().debugMode()) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_LogicalDevice, indices.presentFamily.value(), 0, &m_PresentQueue);
  }

  void VulkanContext::CreateSurface()
  {
      if (glfwCreateWindowSurface(m_Instance, m_Window->GetWindow(), nullptr, &m_Surface) != VK_SUCCESS) {
          throw std::runtime_error("failed to create window surface!");
      }
  }

  bool VulkanContext::CheckValidationLayerSupport()
  {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for(const char *layerName : m_ValidationLayers)
    {
      bool layerFound = false;
      for(const auto &layerProps : availableLayers)
      {
        if(strcmp(layerName, layerProps.layerName) == 0)
        {
          layerFound = true;
          break;
        }
      }

      if(!layerFound)
      {
        return false;
      }
    }
    return true;
   }

  std::vector<const char*> VulkanContext::GetRequiredExtensions()
  {
    uint32_t glfwExtensionCount = 0;

    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions+glfwExtensionCount);

    if(true)
    {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
  }

  bool VulkanContext::IsPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice)
  {
    QueueFamilyIndices indices = FindAvailableQueueFamilies(physicalDevice);
    if (indices.isComplete())
    {
        std::cout << "Suitable Physical Device Found" << std::endl;
    }
    return indices.isComplete();
  }

  QueueFamilyIndices VulkanContext::FindAvailableQueueFamilies(VkPhysicalDevice physicalDevice)
  {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for(const auto &queueFamily : queueFamilies)
    {
      if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
        indices.graphicsFamily = i;
      }

      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, m_Surface, &presentSupport);
      if (presentSupport) {
          indices.presentFamily = i;
      }

      if(indices.isComplete())
      {
        break;
      }

      i++;
    }
    return indices;
  }

  VkResult VulkanContext::CreateDebugUtilsMessengerEXT(
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
    } else {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
  }

  void VulkanContext::DestroyDebugUtilsMessengerEXT(
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


  void VulkanContext::PopulateDebugMessengerCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
  {
      createInfo = {};
      createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
      createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
      createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
      createInfo.pfnUserCallback = debugCallback;
  }


}