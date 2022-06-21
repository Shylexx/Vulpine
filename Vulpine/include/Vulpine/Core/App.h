#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include "Vulpine/Core/Window.h"

int main(int argc, char **argv);

namespace Vulpine
{
    class App
    {
    public:
        App();
        virtual ~App();

        virtual void Update(float deltaTime) {};
        virtual void Render() {};
        virtual void Shutdown() {};

        virtual void Run();

        void CloseApp();

        static void PrintHelloWorld();
        static void DebugLogProps();

        static App &GetInstance() { return *s_Instance; }
        static Window& GetWindow() { return *m_Window; }

    private:
        bool m_Running = true;
        bool m_Minimized = false;

    private:
        static App *s_Instance;
        static Window* m_Window;
        friend int ::main(int argc, char **argv);
    };

    App *CreateApp();
}

#endif
