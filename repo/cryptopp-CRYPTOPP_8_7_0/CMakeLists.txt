project(crypto CXX C)

file(GLOB CRYPTO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(crypto STATIC ${CRYPTO_SRC})
target_include_directories(crypto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})