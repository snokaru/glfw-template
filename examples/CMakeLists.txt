set(GLUT_LIBRARIES opengllib ${OpenGL} ${GLUT})

add_executable(lab7 lab7.cpp)
target_link_libraries(lab7 PUBLIC ${GLUT_LIBRARIES})
target_compile_definitions(lab7 PUBLIC GL_SILENCE_DEPRECATION)

