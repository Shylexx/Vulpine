#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "GameApp.h"
#include <iostream>

extern Vulpine::GameApp *Vulpine::CreateApp();

int main(int argc, char **argv)
{
    std::cout << "Hello Vulpine!" << std::endl;
    Vulpine::GameApp::PrintHelloWorld();

    auto app = Vulpine::CreateApp();
    app->Run();
    delete app;

    return 0;
}

#endif