project(crypto CXX C)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CRYPTO_SRC)

add_library(crypto STATIC ${CRYPTO_SRC})
target_include_directories(crypto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})