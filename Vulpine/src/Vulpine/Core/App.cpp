#include <Vulpine/Core/App.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>

namespace Vulpine
{
    App::App() {
        //s_Instance = this;
    }

    App::~App() = default;

    void App::PrintHelloWorld()
    {
        std::cout << "Hello from GameApp" << std::endl;
    }

    void App::DebugLogProps()
    {
        
    }

    void App::Run()
    {
        // Game Loop
        // while (m_Running)
        // {
        //     Update(deltaTime);
        //     Render();
        // }

        /*if (!glfwInit())
        {
            std::cout << "GLFW Init Failed" << std::endl;
        }


        GLFWwindow* window = glfwCreateWindow(640, 480, "Vulpine Engine", NULL, NULL);

        if (!window) {
            std::cout << "Window Creation Failed" << std::endl;
        }


        std::cout << "Vulpine Engine Init" << std::endl;

        while (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();*/
    }

    void App::CloseApp()
    {
        m_Running = false;
    }
}