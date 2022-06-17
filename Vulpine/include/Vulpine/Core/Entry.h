#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "GameApp.h"
#include <iostream>
#include <GLFW/glfw3.h>

extern Vulpine::GameApp *Vulpine::CreateApp();

int main(int argc, char **argv)
{
    std::cout << "Hello Vulpine!" << std::endl;
    Vulpine::GameApp::PrintHelloWorld();

    if(!glfwInit())
    {
        return 1;
    }


    GLFWwindow* window = glfwCreateWindow(640, 480, "Vulpine Engine", NULL, NULL);

    if (!window) {
        std::cout << "Window Creation Failed" << std::endl;
    }

    auto app = Vulpine::CreateApp();
    app->Run();
    delete app;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

#endif