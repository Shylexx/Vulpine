#include "Vulpine/Render/Vulkan/VulkanDescriptors.h"

namespace Vulpine {

	VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanContext& context)
		: m_Context(context)
	{
	}

	void VulkanDescriptorSetLayout::Init() {
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &uboLayoutBinding;

		if (vkCreateDescriptorSetLayout(m_Context.logicalDevice(), &layoutInfo, nullptr, &m_Layout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Create Descriptor Set Layout!");
		}
	}

	void VulkanDescriptorSetLayout::Cleanup() {
		vkDestroyDescriptorSetLayout(m_Context.logicalDevice(), m_Layout, nullptr);
	}

	VulkanDescriptorPool::VulkanDescriptorPool(VulkanContext& context)
		: m_Context(context)
	{
	}

	void VulkanDescriptorPool::Init(uint32_t maxFrames) {
		VkDescriptorPoolSize poolSize{};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = static_cast<uint32_t>(maxFrames);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = static_cast<uint32_t>(maxFrames);

		if (vkCreateDescriptorPool(m_Context.logicalDevice(), &poolInfo, nullptr, &m_Pool) != VK_SUCCESS) {
			throw std::runtime_error("Failed to Create Descriptor Pool!");
		}
	}

	void VulkanDescriptorPool::Cleanup()
	{
		vkDestroyDescriptorPool(m_Context.logicalDevice(), m_Pool, nullptr);
	}
}