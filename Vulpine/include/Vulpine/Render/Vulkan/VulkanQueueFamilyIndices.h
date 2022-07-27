#ifndef __VK_QUEUE_FAM_IND_H__
#define __VK_QUEUE_FAM_IND_H__

#include <optional>
#include <stdint.h>

namespace Vulpine
{
    struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
}


#endif
