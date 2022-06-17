#include <Vulpine/Core/GameApp.h>
#include <iostream>

namespace Vulpine
{
    GameApp::GameApp() = default;
    GameApp::~GameApp() = default;

    void GameApp::PrintHelloWorld()
    {
        std::cout << "Hello from GameApp" << std::endl;
    }

    void GameApp::Run()
    {
        // Init();
        // while (m_Running)
        // {
        //     Update();
        //     Render();
        // }
        // Shutdown();
        std::cout << "Vulpine Engine Init" << std::endl;
        while (true)
        {
        }
    }

    void GameApp::CloseApp()
    {
        m_Running = false;
    }
}