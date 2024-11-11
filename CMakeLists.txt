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

find_package(OpenGL REQUIRED)

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

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

FetchContent_MakeAvailable(glfw glad glm)

add_executable(pong src/main.cpp)

target_include_directories(pong PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pong PUBLIC glfw glad glm)

