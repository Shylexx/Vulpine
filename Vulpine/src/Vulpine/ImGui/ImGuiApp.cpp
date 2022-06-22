#include "Vulpine/ImGui/ImGuiApp.h"

namespace Vulpine {
	void ImGuiApp::Update(float deltaTime) {
		App::Update(deltaTime);

		m_ImGuiLayer->Update(deltaTime);

		m_ImGuiLayer->Begin();
		m_ImGuiLayer->ImGuiRender();
		m_ImGuiLayer->End();
	}
}