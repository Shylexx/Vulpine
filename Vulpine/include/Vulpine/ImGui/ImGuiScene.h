#ifndef __VP_IMGUI_SCENE_H__
#define __VP_IMGUI_SCENE_H__

#include "Vulpine/Scene/Scene.h"
#include "Vulpine/ImGui/ImGuiLayer.h"

class ImGuiLayer;

namespace Vulpine {
	class ImGuiScene : public Scene {
	public:
		virtual void Update(float deltaTime);
	private:
		ImGuiLayer* m_ImGuiLayer;
	};
}
#endif
