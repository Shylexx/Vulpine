#ifndef __VK_DEBUG_MESSENGER_H__
#define __VK_DEBUG_MESSENGER_H__


namespace Vulpine
{
	class VulkanDebugMessenger
	{
	public:
		VulkanDebugMessenger();
		~VulkanDebugMessenger();
		void Setup();
		void Cleanup();

	};
}
#endif
