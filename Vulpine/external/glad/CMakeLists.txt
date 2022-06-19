cmake_minimum_required(VERSION 3.23)

# glad gl loader with all ARB and EXT functions.
project(glad)

# use those files for the project
set(GLAD_HEADERS
	include/glad/glad.h
	include/KHR/khrplatform.h
)
set(GLAD_SOURCES
	src/glad.c
)

# prepend directories to the files
list(TRANSFORM HEADERS PREPEND include/)
list(TRANSFORM SOURCES PREPEND src/)

# create the static library
add_library(glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})
target_include_directories(glad PUBLIC include)
target_compile_features(glad PUBLIC cxx_std_17)

if(NOT GLAD_CUSTOM_OUTPUT)
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/bin/debug/")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/bin/release/")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/build/bin/MinSizeRel/")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/bin/RelWithDebInfo/")
else()
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${GLAD_CUSTOM_OUTPUT_DEBUG}")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${GLAD_CUSTOM_OUTPUT_RELEASE}")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${GLAD_CUSTOM_OUTPUT_MINSIZEREL}")
	set_target_properties(glad PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${GLAD_CUSTOM_OUTPUT_RELWITHDEBINFO}")
endif()