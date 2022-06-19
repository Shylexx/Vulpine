cmake_minimum_required(VERSION 3.23)
project(Vulpes VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(VULPES_HEADERS
	src/Editor.h
)

set(VULPES_SOURCES
	src/VulpesApp.cpp
	src/Editor.cpp
)

add_executable(${PROJECT_NAME}
	${VULPES_HEADERS}
	${VULPES_SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		src
)

target_link_libraries(${PROJECT_NAME} 
	Vulpine
)