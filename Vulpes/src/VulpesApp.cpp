#include <Vulpine/Core/App.h>
#include <Vulpine/Core/Entry.h>

#include <iostream>

#include "Editor.h"

class SandboxApp : public Vulpine::App
{
public:
    Editor editor;

    SandboxApp()
    {
        App::App();
        editor.RenderEditor();

        // Planned Future API
        // LoadStartupScene();
    }

    ~SandboxApp()
    {
        App::~App();
    }
};

Vulpine::App* Vulpine::CreateApp()
{
    return new SandboxApp();
}