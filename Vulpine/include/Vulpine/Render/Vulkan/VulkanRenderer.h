#ifndef __VK_RENDERER_H__
#define __VK_RENDERER_H__

#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Render/Vulkan/VulkanContext.h>
#include <Vulpine/Render/Vulkan/VulkanSwapChain.h>
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
  std::unique_ptr<VulkanPipeline> m_Pipeline;
  std::unique_ptr<VulkanBuffer> m_VertexBuffer;

  void CreateCommandBuffers();

  void BeginRenderPass(VkCommandBuffer commandBuffer);
  void EndRenderPass(VkCommandBuffer commandBuffer);

  std::vector<VkCommandBuffer> m_CommandBuffers;

  uint32_t m_CurrentImage;
};

}
#endif
