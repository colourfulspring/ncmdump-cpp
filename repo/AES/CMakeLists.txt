project(AES CXX)

add_library(AES STATIC src/AES.cpp src/AES.h)
target_include_directories(AES PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)