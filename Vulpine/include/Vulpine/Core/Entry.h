#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "App.h"
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

extern Vulpine::App *Vulpine::CreateApp();

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int argc, char **argv)
{
    std::cout << "Hello Vulpine!" << std::endl;
    Vulpine::App::PrintHelloWorld();

    // Init
    auto app = Vulpine::CreateApp();
    app->Init();

    // Runtime
    app->Run();

    // Cleanup
    app->Cleanup();
    delete app;

    return 0;
}

#endif