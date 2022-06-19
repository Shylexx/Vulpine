cmake_minimum_required (VERSION 3.23)
project(Vulpine_Libs VERSION 0.0.1 LANGUAGES CXX C)



set(IMGUI_SOURCES
        "imgui/imgui.cpp"
        "imgui/imgui_demo.cpp"
        "imgui/imgui_draw.cpp"
		"imgui/imgui_tables.cpp"
		"imgui/imgui_widgets.cpp"
"imgui/backends/imgui_impl_glfw.cpp"
	"imgui/backends/imgui_impl_opengl3.cpp")

set(IMGUI_HEADERS
        "imgui/imconfig.h"
        "imgui/imgui.h"
        "imgui/imgui_internal.h"
        "imgui/imstb_rectpack.h"
        "imgui/imstb_textedit.h"
        "imgui/imstb_truetype.h"
	"imgui/backends/imgui_impl_glfw.h"
	"imgui/backends/imgui_impl_opengl3.h")

add_library(ImGui ${IMGUI_SOURCES} ${IMGUI_HEADERS})

target_include_directories(ImGui 
	PUBLIC
		imgui
	PRIVATE
		glfw
)

target_link_libraries(ImGui
	PRIVATE
		glfw
)