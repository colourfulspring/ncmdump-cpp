cmake_minimum_required(VERSION 3.17)

project(ncmdump CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 89)

set(BUILD_TEST off)

add_subdirectory(repo)

file(GLOB src utils/*.h utils/*.cpp)
list(APPEND src main.cpp)
add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE AES)
target_link_libraries(${PROJECT_NAME} PRIVATE base64)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_lib)

if (BUILD_TEST)
    add_subdirectory(test)
endif ()