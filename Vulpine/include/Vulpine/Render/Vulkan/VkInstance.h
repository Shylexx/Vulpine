#ifndef __VK_INSTANCE_H__
#define __VK_INSTANCE_H__

namespace Vulpine
{
class VulkanInstance
{
	public:
		VulkanInstance();
		void CreateInstance();
		void Cleanup();
};

}
#endif
