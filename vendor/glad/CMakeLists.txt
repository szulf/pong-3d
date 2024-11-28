cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

add_library(glad STATIC src/glad.c)
set_source_files_properties(src/glad.c PROPERTIES LANGUAGE CXX)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
