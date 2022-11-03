#ifndef __VK_DESCRIPTORS_H__
#define __VK_DESCRIPTORS_H__

#include <vulkan/vulkan.h>
#include "Vulpine/Render/Vulkan/VulkanContext.h"

namespace Vulpine {
	class VulkanDescriptorSetLayout {
	public:
		VulkanDescriptorSetLayout(VulkanContext& context);
		void Init();
		void Cleanup();
		VkDescriptorSetLayout layout() { return m_Layout; }
	private:
		VkDescriptorSetLayout m_Layout = VK_NULL_HANDLE;

		VulkanContext& m_Context;
	};

	class VulkanDescriptorPool {
	public:
		VulkanDescriptorPool(VulkanContext& context);
		void Init(uint32_t maxFrames);
		void Cleanup();
		VkDescriptorPool pool() { return m_Pool; }
	private:
		VkDescriptorPool m_Pool = VK_NULL_HANDLE;

		VulkanContext& m_Context;
	};
}

#endif