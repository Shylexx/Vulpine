#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

int main(int argc, char **argv);

namespace Vulpine
{
    class GameApp
    {
    public:
        GameApp();
        virtual ~GameApp();

        void Init();
        void Update();
        void Render();
        void Shutdown();

        void Run();

        void CloseApp();

        static void PrintHelloWorld();

        static GameApp &GetInstance() { return *s_Instance; }

    private:
        bool m_Running = true;
        bool m_Minimized = false;

    private:
        static GameApp *s_Instance;
        friend int ::main(int argc, char **argv);
    };

    GameApp *CreateApp();
}

#endif
