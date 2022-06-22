#ifndef __VP_IMGUI_LAYER_H__
#define __VP_IMGUI_LAYER_H__

#include "Vulpine/Scene/Layer.h"


namespace Vulpine {
	class ImGuiLayer : public Layer {
	public:
		void Update(float deltaTime) override{};
		void ImGuiRender();
		void Begin();
		void End();

	};

}
#endif