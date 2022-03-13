set(SRC_FILES "Window.cpp")

add_executable("lab2-1" "lab2-1.cpp" ${SRC_FILES})
add_executable("lab2-2" "lab2-2.cpp" ${SRC_FILES})

target_link_libraries("lab2-1" PUBLIC glfw glad)
target_link_libraries("lab2-2" PUBLIC glfw glad)
