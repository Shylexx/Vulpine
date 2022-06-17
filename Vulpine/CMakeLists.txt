cmake_minimum_required(VERSION 3.23)
project(Vulpine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)

set(VULPINE_HEADERS
    include/Vulpine/Core/Entry.h
    include/Vulpine/Core/GameApp.h
)

set(VULPINE_SOURCES
    src/Vulpine/Core/GameApp.cpp)

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
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
	glm
	glfw
)

