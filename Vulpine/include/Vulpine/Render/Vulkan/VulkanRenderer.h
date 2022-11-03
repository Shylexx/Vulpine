#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Render/Vulkan/VulkanContext.h>
#include <Vulpine/Render/Vulkan/VulkanSwapChain.h>
#include <Vulpine/Render/Vulkan/VulkanDescriptors.h>
#include <Vulpine/Render/Vulkan/VulkanBuffer.h>
#include <Vulpine/Core/Window.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Vulpine
{

class VulkanRenderer
{
public:
	VulkanRenderer(Window *window);
	~VulkanRenderer() = default;

	void Init();
	void Cleanup();

  void DrawFrame();
  void BeginRecordCommand(VkCommandBuffer commandBuffer);
  void Render(VkCommandBuffer commandBuffer);
  void EndRecordCommand(VkCommandBuffer commandBuffer);
private:
  std::unique_ptr<VulkanContext> m_Context;
  std::unique_ptr<VulkanSwapChain> m_SwapChain;
  std::unique_ptr<VulkanDescriptorSetLayout> m_DescriptorSetLayout;
  std::unique_ptr<VulkanDescriptorPool> m_DescriptorPool;
  std::unique_ptr<VulkanPipeline> m_Pipeline;
  std::unique_ptr<VulkanBuffer> m_VertexBuffer;
  std::unique_ptr<VulkanBuffer> m_VertexStagingBuffer;
  std::unique_ptr<VulkanBuffer> m_IndexBuffer;
  std::unique_ptr<VulkanBuffer> m_IndexStagingBuffer;
  std::vector<std::unique_ptr<VulkanBuffer>> m_UniformBuffers;
  std::vector<VkDescriptorSet> m_DescriptorSets;

  void CreateCommandBuffers();
  void CreateDescriptorSets();
  void MapToBuffer(VulkanBuffer& buffer, void* data);
  void UpdateUniformBuffer(uint32_t currentImage);

  void BeginRenderPass(VkCommandBuffer commandBuffer);
  void EndRenderPass(VkCommandBuffer commandBuffer);

  std::vector<VkCommandBuffer> m_CommandBuffers;

  uint32_t m_CurrentImage;
};

}
#endif
