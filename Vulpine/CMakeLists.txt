cmake_minimum_required(VERSION 3.23)
project(Vulpine VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external)
add_subdirectory(external/glad)


set(VULPINE_HEADERS
    include/Vulpine.h
    include/vppch.h
    include/Vulpine/Core/Entry.h
    include/Vulpine/Core/App.h
    include/Vulpine/Core/Window.h
    include/Vulpine/Scene/Scene.h
    include/Vulpine/Scene/Layer.h
    include/Vulpine/ImGui/ImGuiApp.h
    include/Vulpine/ImGui/ImGuiLayer.h
    include/Vulpine/ImGui/ImGuiScene.h
)

set(VULPINE_SOURCES
    src/vppch.cpp
    src/Vulpine/Core/App.cpp
    src/Vulpine/Core/Window.cpp
    src/Vulpine/Scene/Scene.cpp
    src/Vulpine/Scene/Layer.cpp
    src/Vulpine/ImGui/ImGuiApp.cpp
    src/Vulpine/ImGui/ImGuiLayer.cpp
    src/Vulpine/ImGui/ImGuiScene.cpp
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
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
	glm
	glfw
	ImGui
	glad
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC GLFW_INCLUDE_NONE
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE include/vppch.h
)
	

