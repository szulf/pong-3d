cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(pong
        VERSION 1.0
        DESCRIPTION "Simple pong game with 3d graphics"
        LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
    FIND_PACKAGE_ARGS 3.4
)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz
    FIND_PACKAGE_ARGS 1.0.1
)

FetchContent_MakeAvailable(glfw glm)

add_subdirectory(vendor/glad)

add_executable(pong src/main.cpp
    src/Game.cpp include/Game.hpp
    src/Window.cpp include/Window.hpp
    src/Shader.cpp include/Shader.hpp
    src/VertexArray.cpp include/VertexArray.hpp
    src/VertexBuffer.cpp include/VertexBuffer.hpp
)

target_include_directories(pong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pong PUBLIC glfw glad glm)

target_compile_options(pong PRIVATE
    -Wall -Werror -pedantic
)
