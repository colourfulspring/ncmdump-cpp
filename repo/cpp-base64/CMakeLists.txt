project(base64 CXX)

add_library(base64 STATIC base64.cpp base64.h)
target_include_directories(base64 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})