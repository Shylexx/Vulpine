#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include "Vulpine/Core/Window.h"
#include "Vulpine/Scene/Scene.h"

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

        static void PrintHelloWorld();
        static void DebugLogProps();

        static App &GetInstance() { return *s_Instance; }
        Window* m_Window;
    private:
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0;

    private:
        static App *s_Instance;
        
        Scene *m_CurrentScene;

        friend int ::main(int argc, char **argv);
        WindowProperties m_WindowProps;
    };

    App *CreateApp();
}

#endif
