#ifndef __VP_IMGUI_APP_H__
#define __VP_IMGUI_APP_H__

#include "Vulpine/Core/App.h"

namespace Vulpine {
	class ImGuiApp : public App
	{
	public:
		virtual void Update(float deltaTime) override {};
		virtual void ImGuiRender() {};

		virtual void Run() override {};

	};
}

#endif