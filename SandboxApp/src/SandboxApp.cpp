#include <Vulpine/Core/App.h>
#include <Vulpine/Core/Entry.h>

#include <iostream>

class SandboxApp : public Vulpine::App
{
public:
    SandboxApp()
    {
        std::cout << "Sandbox App Init" << std::endl;
    }

    ~SandboxApp()
    {
    }
};

Vulpine::App* Vulpine::CreateApp()
{
    return new SandboxApp();
}