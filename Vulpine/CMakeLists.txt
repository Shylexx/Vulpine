cmake_minimum_required(VERSION 3.23)
project(Vulpine VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external)
add_subdirectory(external/glad)

# add OpenGL
find_package(OpenGL REQUIRED)

# imgui sources
set(IMGUI_SOURCES
	external/imgui/imgui.cpp
	external/imgui/imgui_draw.cpp
	external/imgui/imgui_demo.cpp
	external/imgui/imgui_tables.cpp
	external/imgui/imgui_widgets.cpp
	external/imgui/backends/imgui_impl_glfw.cpp
	external/imgui/backends/imgui_impl_opengl3.cpp
	external/imgui/imgui.h
	external/imgui/backends/imgui_impl_glfw.h
	external/imgui/backends/imgui_impl_opengl3.h
)

set(VULPINE_HEADERS
    include/Vulpine/Core/Entry.h
    include/Vulpine/Core/App.h
	include/Vulpine/Core/Window.h
)

set(VULPINE_SOURCES
    src/Vulpine/Core/App.cpp
	src/Vulpine/Core/Window.cpp
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

