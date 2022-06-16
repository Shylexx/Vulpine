cmake_minimum_required(VERSION 3.23)
project(VulpineApp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(VulpineApp src/main.cpp)

target_link_libraries(VulpineApp Vulpine)
target_include_directories(VulpineApp PRIVATE Vulpine)