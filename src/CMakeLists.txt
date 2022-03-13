set(SRC_FILES "Window.cpp")

add_executable("lab3-1" "lab3-1.cpp" ${SRC_FILES})
add_executable("lab3-2" "lab3-2.cpp" ${SRC_FILES})

target_link_libraries("lab3-1" PUBLIC glfw glad)
target_link_libraries("lab3-2" PUBLIC glfw glad)
