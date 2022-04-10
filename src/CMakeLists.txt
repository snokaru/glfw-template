set(SRC_FILES "Texture2D.cpp")
set(THIRD_PARTY_LIBRARIES stb_image ${OpenGL} ${GLUT})

add_library(opengllib ${SRC_FILES})
target_include_directories(opengllib PUBLIC ../include)
target_link_libraries(opengllib PUBLIC ${THIRD_PARTY_LIBRARIES})
target_compile_definitions(opengllib PRIVATE STB_IMAGE_IMPLEMENTATION GL_SILENCE_DEPRECATION)
