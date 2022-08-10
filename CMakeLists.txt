cmake_minimum_required(VERSION 3.17)
project(ncm_dump CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 89)

# Custom options
set(BUILD_TEST on)

# Add modules
add_subdirectory(repo)

# Add executable
add_executable(ncm_dump main.cpp)

# Link libraries
target_link_libraries(ncm_dump PRIVATE binascii)
target_link_libraries(ncm_dump PRIVATE AES)

# Build test
if (BUILD_TEST)
    add_executable(test test.cpp)
    target_link_libraries(test PRIVATE crypto)
endif()