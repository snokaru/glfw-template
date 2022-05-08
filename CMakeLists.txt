cmake_minimum_required(VERSION 3.22)

project(OpenGLTest VERSION 1.0
                   DESCRIPTION "Stuff implemented in Computer Graphics Class")

find_package(glfw3 3.3.6 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(examples)
