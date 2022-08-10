project(binascii C)

add_library(binascii STATIC binascii.h binascii.c)
target_include_directories(binascii PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})