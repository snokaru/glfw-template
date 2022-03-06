add_executable(${PROJECT_NAME} "main.cpp" "Vector2f.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad)
