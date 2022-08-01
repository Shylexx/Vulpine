#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include <memory>

#include "Vulpine/Core/Window.h"
#include "Vulpine/Scene/Scene.h"
#include <Vulpine/Render/Vulkan/VulkanRenderer.h>

int main(int argc, char **argv);

namespace Vulpine
{
    class App
    {
    public:
        App();
        virtual ~App();

        virtual void Update(float deltaTime);
        virtual void Render(){};
        virtual void Shutdown(){};

        virtual void Run();

        void CloseApp();

        static void DebugLogProps();

        static App &GetInstance() { return *s_Instance; }
        static Window *GetWindow()
        {
            return s_Instance->m_Window.get();
        }

		bool debugMode() { return m_DebugMode; }

    private:
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0;
        bool m_DebugMode = true;
        std::unique_ptr<Window> m_Window;

    private:
        static App *s_Instance;

        Scene *m_CurrentScene;

        std::unique_ptr<VulkanRenderer> m_Renderer;

        friend int ::main(int argc, char **argv);
        WindowProperties m_WindowProps;
    };

    App *CreateApp();
}

#endif
