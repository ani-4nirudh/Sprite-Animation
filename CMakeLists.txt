cmake_minimum_required(VERSION 3.16)
project(dog)

# Set output directory for build files
## CMAKE_BINARY_DIR = build/
## CONFIGURATION = Generator expression. CMake automatically replaces <CONFIGURATION> with name of build configuration you are currently using
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/SDL_image EXCLUDE_FROM_ALL)

add_executable(dog main.cpp)
target_compile_options(dog PRIVATE -std=c++17 -ggdb3)
target_link_libraries(dog PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)