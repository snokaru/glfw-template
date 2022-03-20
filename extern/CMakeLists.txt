set(GLAD_LIB_NAME "glad")
set(GLAD_SRC_PATH "${GLAD_LIB_NAME}/src")
set(GLAD_INC_PATH "${GLAD_LIB_NAME}/include")

add_library(${GLAD_LIB_NAME} STATIC "${GLAD_SRC_PATH}/glad.c")
target_include_directories(${GLAD_LIB_NAME} PUBLIC "${GLAD_INC_PATH}")

set(STB_LIB_NAME "stb_image")
set(STB_INC_PATH "${STB_LIB_NAME}/include")

add_library(${STB_LIB_NAME} INTERFACE)
target_include_directories(${STB_LIB_NAME} INTERFACE "${STB_INC_PATH}")

