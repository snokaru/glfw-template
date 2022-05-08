set(GLUT_LIBRARIES opengllib ${OpenGL} ${GLUT})

# add_executable(lab7 lab7.cpp)
# target_link_libraries(lab7 PUBLIC ${GLUT_LIBRARIES})
# target_compile_definitions(lab7 PUBLIC GL_SILENCE_DEPRECATION)
#
# add_executable(lab9 lab9.cpp)
# target_link_libraries(lab9 PUBLIC ${GLUT_LIBRARIES})
# target_compile_definitions(lab9 PUBLIC GL_SILENCE_DEPRECATION)

add_executable(lab11 lab11.cpp)
target_link_libraries(lab11 PUBLIC ${GLUT_LIBRARIES})
target_compile_definitions(lab11 PUBLIC GL_SILENCE_DEPRECATION)
