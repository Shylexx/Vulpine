#include <Vulpine/ImGui/ImGuiApp.h>
#include <Vulpine/Core/Entry.h>

#include <iostream>

#include "Editor.h"

class SandboxApp : public Vulpine::App
{
public:
    Editor editor;

    SandboxApp()
    {
        //editor.RenderEditor();

        // Planned Future API
        // LoadStartupScene();
    }

    ~SandboxApp()
    {
    }
};

Vulpine::App* Vulpine::CreateApp()
{
    return new SandboxApp();
}