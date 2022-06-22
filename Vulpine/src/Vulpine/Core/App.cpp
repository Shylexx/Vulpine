#include <Vulpine/Core/App.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>

namespace Vulpine
{
    App* App::s_Instance;
    Window* App::s_Window;

    App::App() {
        s_Instance = this;
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
        float time = (float)glfwGetTime();
        float deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;

        while (m_Running)
        {
            Update(deltaTime);

        }

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

    void App::Update(float deltaTime)
    {
        m_CurrentScene->Update(deltaTime);
    }

    void App::CloseApp()
    {
        m_Running = false;
    }
}