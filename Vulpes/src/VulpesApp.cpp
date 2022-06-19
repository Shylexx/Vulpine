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
        editor.RenderEditor();
    }

    ~SandboxApp()
    {
    }
};

Vulpine::App* Vulpine::CreateApp()
{
    return new SandboxApp();
}