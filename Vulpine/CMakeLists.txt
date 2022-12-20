cmake_minimum_required(VERSION 3.23)
project(Vulpine VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
endif()

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external)
add_subdirectory(external/entt)
add_subdirectory(external/VMA)
add_subdirectory(external/volk)

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
    include/Vulpine/ImGui/ImGuiApp.h
    include/Vulpine/Render/Vulkan/VulkanRenderer.h
    include/Vulpine/Render/Vulkan/VulkanContext.h
    include/Vulpine/Render/Vulkan/VulkanSwapChain.h
    include/Vulpine/Render/Vulkan/VulkanPipeline.h
    include/Vulpine/Render/Vulkan/VulkanBuffer.h
    include/Vulpine/Render/Vulkan/VulkanDescriptors.h
    include/Vulpine/Scene/CoreComponents.h
    include/Vulpine/Scene/Entity.h
)

set(VULPINE_SOURCES
    src/vppch.cpp
    src/Vulpine/Core/App.cpp
    src/Vulpine/Core/Window.cpp
    src/Vulpine/Scene/Scene.cpp
    src/Vulpine/ImGui/ImGuiApp.cpp
    src/Vulpine/Render/Vulkan/VulkanRenderer.cpp
    src/Vulpine/Render/Vulkan/VulkanContext.cpp
    src/Vulpine/Render/Vulkan/VulkanSwapChain.cpp
    src/Vulpine/Render/Vulkan/VulkanPipeline.cpp
    src/Vulpine/Render/Vulkan/VulkanBuffer.cpp
    src/Vulpine/Render/Vulkan/VulkanDescriptors.cpp
    src/Vulpine/Scene/Entity.cpp
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
    volk
    VMA
    external/imgui
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm
    glfw
    ImGui
    VulkanMemoryAllocator
    volk
    ${Vulkan_LIBRARIES}
    EnTT::EnTT
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC GLFW_INCLUDE_NONE
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE include/vppch.h
)

# Copy Shaders over to build
file(COPY
	shaders
	DESTINATION
	${CMAKE_BINARY_DIR}
)
