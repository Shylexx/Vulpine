#ifndef __ENGINE_H__
#define __ENGINE_H__

class Engine
{
public:
    Engine();
    ~Engine();

    void Init();
    void Update();
    void Render();
    void Shutdown();

    static void PrintHelloWorld();
};

#endif