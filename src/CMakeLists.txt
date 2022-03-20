set(SRC_FILES "Window.cpp" "Texture2D.cpp" "Sprite.cpp")
set(THIRD_PARTY_LIBRARIES stb_image glfw glad)

add_library(opengllib ${SRC_FILES})
target_include_directories(opengllib PUBLIC ../include)
target_link_libraries(opengllib PUBLIC ${THIRD_PARTY_LIBRARIES})
target_compile_definitions(opengllib PRIVATE STB_IMAGE_IMPLEMENTATION)
