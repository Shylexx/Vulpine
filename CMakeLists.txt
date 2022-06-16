cmake_minimum_required(VERSION 3.23)
project(VulpineEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Application)
add_subdirectory(Vulpine)

# add_subdirectory(Vulpes)

# # Static Engine Library
# add_library(Vulpine STATIC)

# set(Vulpine_HEADERS
# "Vulpine.h")

# set(Vulpine_SRC
# "Vulpine.cpp")

# target_sources(Vulpine PRIVATE
# ${Vulpine_HEADERS}
# ${Vulpine_SRC})

# # Sandbox Application
# add_executable(Sandbox)

# set(Sandbox_HEADERS
# "Sandbox.h")

# set(Sandbox_SRC
# "Sandbox.cpp")

# target_sources(Sandbox PRIVATE
# ${Sandbox_SRC}
# ${Sandbox_HEADERS})

# target_link_libraries(Sandbox PRIVATE Vulpine)