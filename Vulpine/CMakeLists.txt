cmake_minimum_required(VERSION 3.23)
project(Vulpine VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external)
add_subdirectory(external/glad)

# Add Vulkan
find_package(Vulkan REQUIRED)

if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "Could not find Vulkan library!")
else()
    message(STATUS "Using vulkan lib at: ${Vulkan_LIBRARIES}")
endif()

set(VULPINE_HEADERS
    include/Vulpine.h
    include/vppch.h
    include/Vulpine/Core/Entry.h
    include/Vulpine/Core/App.h
    include/Vulpine/Core/Window.h
    include/Vulpine/Scene/Scene.h
    include/Vulpine/Core/Layer.h
    include/Vulpine/ImGui/ImGuiApp.h
    include/Vulpine/ImGui/ImGuiLayer.h
    include/Vulpine/ImGui/ImGuiScene.h
    include/Vulpine/Render/Vulkan/VulkanRenderer.h
    include/Vulpine/Render/Vulkan/VulkanContext.h
    include/Vulpine/Render/Vulkan/VulkanSwapChain.h
    include/Vulpine/Render/Vulkan/VulkanPipeline.h
    include/Vulpine/Scene/CoreComponents.h
)

set(VULPINE_SOURCES
    src/vppch.cpp
    src/Vulpine/Core/App.cpp
    src/Vulpine/Core/Window.cpp
    src/Vulpine/Scene/Scene.cpp
    src/Vulpine/Core/Layer.cpp
    src/Vulpine/ImGui/ImGuiApp.cpp
    src/Vulpine/ImGui/ImGuiLayer.cpp
    src/Vulpine/ImGui/ImGuiScene.cpp
    src/Vulpine/Render/Vulkan/VulkanRenderer.cpp
    src/Vulpine/Render/Vulkan/VulkanContext.cpp
    src/Vulpine/Render/Vulkan/VulkanSwapChain.cpp
    src/Vulpine/Render/Vulkan/VulkanPipeline.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${VULPINE_SOURCES}
    ${VULPINE_HEADERS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    glm
    glfw
    external/imgui
    external/glad/include
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm
    glfw
    ImGui
    glad
    ${Vulkan_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC GLFW_INCLUDE_NONE
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE include/vppch.h
)
