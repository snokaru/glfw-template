set(STB_LIB_NAME "stb_image")
set(STB_INC_PATH "${STB_LIB_NAME}/include")

add_library(${STB_LIB_NAME} INTERFACE)
target_include_directories(${STB_LIB_NAME} INTERFACE "${STB_INC_PATH}")

find_library(OpenGL "OpenGL")
find_library(GLUT "GLUT")
