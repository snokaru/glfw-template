set(LIBRARIES "opengllib")

add_executable(lab3-1 lab3-1.cpp)
add_executable(lab3-2 lab3-2.cpp)
add_executable(lab4-1 lab4-1.cpp)

target_link_libraries(lab3-1 PUBLIC ${LIBRARIES})
target_link_libraries(lab3-2 PUBLIC ${LIBRARIES})
target_link_libraries(lab4-1 PUBLIC ${LIBRARIES})
