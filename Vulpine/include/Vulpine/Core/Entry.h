#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "App.h"
#include <iostream>

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

extern Vulpine::App *Vulpine::CreateApp();

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int argc, char **argv)
{
    std::cout << "Hello Vulpine!" << std::endl;

    // Init
    std::cout << "App Initialisation" << std::endl;
    auto app = Vulpine::CreateApp();

    // Runtime
    std::cout << "App Runtime" << std::endl;
    app->Run();

    // Cleanup
    std::cout << "App Cleanup" << std::endl;
    delete app;

    return 0;
}

#endif