#include <Vulpine/Core/GameApp.h>
#include <Vulpine/Core/Entry.h>

#include <iostream>

class SandboxApp : public Vulpine::GameApp
{
public:
    SandboxApp()
    {
    }

    ~SandboxApp()
    {
    }
};

Vulpine::GameApp *Vulpine::CreateApp()
{
    return new SandboxApp();
}