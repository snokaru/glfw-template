cmake_minimum_required(VERSION 3.22)

project(OpenGLTest VERSION 1.0
                   DESCRIPTION "Stuff implemented in Computer Graphics Class")

find_package(glfw3 3.3.6 REQUIRED)

add_subdirectory(extern)
add_subdirectory(src)
