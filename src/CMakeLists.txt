set(SRC_FILES "Window.cpp")
set(THIRD_PARTY_LIBRARIES glfw glad stb_image)

add_executable("lab3-1" "lab3-1.cpp" ${SRC_FILES})
add_executable("lab3-2" "lab3-2.cpp" ${SRC_FILES})

target_link_libraries("lab3-1" PUBLIC ${THIRD_PARTY_LIBRARIES})
target_link_libraries("lab3-2" PUBLIC ${THIRD_PARTY_LIBRARIES})
