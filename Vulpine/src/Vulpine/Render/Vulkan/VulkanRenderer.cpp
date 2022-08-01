
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>
#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <Vulpine/Core/App.h>
#include <stdexcept>

namespace Vulpine
{

	VulkanRenderer::VulkanRenderer(Window *window)
	{
	m_Context = std::make_unique<VulkanContext>();
    m_SwapChain = std::make_unique<VulkanSwapChain>(*m_Context);
    m_Pipeline = std::make_unique<VulkanPipeline>(*m_Context, *m_SwapChain);
	}

	void VulkanRenderer::Init()
	{
	m_Context->CreateContext();
    m_SwapChain->Init();
    m_Pipeline->Init();
    CreateCommandBuffers();
	}

	void VulkanRenderer::Cleanup()
	{
    vkDeviceWaitIdle(m_Context->logicalDevice());

    m_SwapChain->Cleanup();
    m_Pipeline->Cleanup();
	m_Context->Cleanup();
    
	}

  void VulkanRenderer::CreateCommandBuffers()
  {
    m_CommandBuffers.resize(m_SwapChain->MaxFrames());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_Context->commandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

    if(vkAllocateCommandBuffers(m_Context->logicalDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Allocate Command Buffers!");
    }
  }

  void VulkanRenderer::DrawFrame()
  {
    // Skips Frame Draw if New Swap Chain Created
    if (!m_SwapChain->AcquireNextImage(&m_CurrentImage))
    {
        return;
    }
   
    BeginRecordCommand(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

    BeginRenderPass(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

    Render(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

    EndRenderPass(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

    EndRecordCommand(m_CommandBuffers[m_SwapChain->CurrentFrame()]);

  }

  void VulkanRenderer::BeginRecordCommand(VkCommandBuffer commandBuffer)
  {
    vkResetCommandBuffer(commandBuffer, 0);

    VkCommandBufferBeginInfo beginInfo {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Begin Command Buffer");
    }
  }

  void VulkanRenderer::Render(VkCommandBuffer commandBuffer)
  {
    m_Pipeline->Bind(commandBuffer);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_SwapChain->extent().width);
    viewport.height = static_cast<float>(m_SwapChain->extent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0,0};
    scissor.extent = m_SwapChain->extent();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
  }

  void VulkanRenderer::EndRecordCommand(VkCommandBuffer commandBuffer)
  {
    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
      throw std::runtime_error("Failed to Record Command Buffer");
    }

    auto swapChainStatus = m_SwapChain->SubmitCommandBuffers(&commandBuffer, &m_CurrentImage);
    if (swapChainStatus == VK_ERROR_OUT_OF_DATE_KHR || swapChainStatus == VK_SUBOPTIMAL_KHR || App::GetWindow()->wasWindowResized())
    {
        App::GetWindow()->resetWindowResizedFlag();
        m_SwapChain->RecreateSwapChain();
    }
    else if (swapChainStatus != VK_SUCCESS) {
        throw std::runtime_error("Failed to Present Image from Swap Chain");
    }
  }

  void VulkanRenderer::BeginRenderPass(VkCommandBuffer commandBuffer)
  {
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_SwapChain->renderPass();
    renderPassInfo.framebuffer = m_SwapChain->GetFrameBuffer(m_CurrentImage);
    renderPassInfo.renderArea.offset = {0,0};
    renderPassInfo.renderArea.extent = m_SwapChain->extent();
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  }

  void VulkanRenderer::EndRenderPass(VkCommandBuffer commandBuffer)
  {
    vkCmdEndRenderPass(commandBuffer);
  }
}
