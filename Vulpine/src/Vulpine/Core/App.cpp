#include <Vulpine/Core/App.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>

namespace Vulpine
{
    App *App::s_Instance;

    App::App()
    {
        s_Instance = this;
        m_Running = true;
        m_Window = std::make_unique<Window>(m_WindowProps);
        m_Renderer = std::make_unique<VulkanRenderer>();
    }

    App::~App()
    {
        glfwTerminate();
    }

    void App::DebugLogProps()
    {
    }

    void App::Run()
    {
        // Init
        float time = (float)glfwGetTime();
        m_Renderer->Init();

        // Game Loop
        while (m_Running)
        {

            time = (float)glfwGetTime();
            float deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;
            Update(deltaTime);

            glfwSwapBuffers(static_cast<GLFWwindow *>(m_Window->GetWindow()));
            glfwPollEvents();

            if (glfwWindowShouldClose(static_cast<GLFWwindow *>(m_Window->GetWindow())))
            {
                m_Running = false;
            }
        }

        m_Renderer->Cleanup();

    }

    void App::Update(float deltaTime)
    {
        m_Window->Update(deltaTime);
        // m_CurrentScene->Update(deltaTime);
        // std::cout << "Update" << std::endl;
    }

    void App::CloseApp()
    {
        m_Running = false;
    }
}