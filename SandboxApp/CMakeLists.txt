cmake_minimum_required(VERSION 3.23)
project(VulpineApp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/SandboxApp.cpp
)

target_link_libraries(${PROJECT_NAME}
    Vulpine
)

set(SANDBOX_SOURCES
    src/SandboxApp.cpp
)
