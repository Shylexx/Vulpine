#ifndef __VP_IMGUI_APP_H__
#define __VP_IMGUI_APP_H__

#include "Vulpine/Core/App.h"
#include "Vulpine/ImGui/ImGuiLayer.h"

namespace Vulpine {
	class ImGuiApp : public App
	{
	public:
		virtual void Update(float deltaTime) override;

		//virtual void Run() override {};
	private:
		ImGuiLayer* m_ImGuiLayer;
	};
}

#endif