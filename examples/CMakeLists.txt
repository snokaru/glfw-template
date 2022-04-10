set(LIBRARIES "opengllib")
set(GLUT_LIBRARIES ${OpenGL} ${GLUT})

add_executable(lab3-1 lab3-1.cpp)
target_link_libraries(lab3-1 PUBLIC ${LIBRARIES})

add_executable(lab3-2 lab3-2.cpp)
target_link_libraries(lab3-2 PUBLIC ${LIBRARIES})

add_executable(lab4-1 lab4-1.cpp)
target_link_libraries(lab4-1 PUBLIC ${LIBRARIES})

add_executable(lab4-2 lab4-2.cpp)
target_link_libraries(lab4-2 PUBLIC ${LIBRARIES})

add_executable(lab4-3 lab4-3.cpp)
target_link_libraries(lab4-3 PUBLIC ${LIBRARIES})

add_executable(lab7 lab7.cpp)
target_link_libraries(lab7 PUBLIC ${GLUT_LIBRARIES})
target_compile_definitions(lab7 PUBLIC GL_SILENCE_DEPRECATION)

