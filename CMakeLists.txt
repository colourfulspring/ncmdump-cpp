cmake_minimum_required(VERSION 3.17)
project(ncm_dump CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 89)

add_subdirectory(repo)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE binascii)
target_link_libraries(${PROJECT_NAME} PRIVATE AES)
target_link_libraries(${PROJECT_NAME} PRIVATE base64)

get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})

target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_lib)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE jsoncpp_lib)
