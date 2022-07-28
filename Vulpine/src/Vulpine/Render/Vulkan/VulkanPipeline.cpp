#include "Vulpine/Render/Vulkan/VulkanContext.h"
#include <Vulpine/Render/Vulkan/VulkanPipeline.h>
#include <fstream>
#include <stdexcept>
#include <vulkan/vulkan_core.h>

namespace Vulpine
{
  VulkanPipeline::VulkanPipeline(VulkanContext& context)
    : m_Context(context)
  {
  }

  void VulkanPipeline::Init()
  {
  }

  void VulkanPipeline::Cleanup()
  {
  }

  void VulkanPipeline::CreatePipeline()
  {
    auto vertShaderCode = ReadFile("shaders/vert.spv");
    auto fragShaderCode = ReadFile("shaders/frag.spv");

    VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    vertShaderStageInfo.module = fragShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    vkDestroyShaderModule(m_Context.logicalDevice(), vertShaderModule, nullptr);
    vkDestroyShaderModule(m_Context.logicalDevice(), fragShaderModule, nullptr);
  }

  std::vector<char> VulkanPipeline::ReadFile(const std::string& filepath)
  {
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if(!file.is_open()) {
      throw std::runtime_error("Failed to Open File!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
  }

  VkShaderModule VulkanPipeline::CreateShaderModule(const std::vector<char>& code)
  {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if(vkCreateShaderModule(m_Context.logicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
      throw std::runtime_error("Failed to create Shader Module!");
    }
    return shaderModule;
  }

}
