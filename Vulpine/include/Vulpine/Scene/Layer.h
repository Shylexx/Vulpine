#ifndef __VP_LAYER_H__
#define __VP_LAYER_H__

#include <string>

namespace Vulpine {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnUpdate(float deltaTime) {};
		virtual void onEvent() {};
	protected:
		std::string m_DebugName;
	};
}
#endif