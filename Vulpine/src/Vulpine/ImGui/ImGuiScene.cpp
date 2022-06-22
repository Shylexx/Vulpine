#include "Vulpine/ImGui/ImGuiScene.h"

namespace Vulpine {
	void ImGuiScene::Update(float deltaTime) {
		m_ImGuiLayer->ImGuiRender();
	}
}