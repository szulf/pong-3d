#include "Game.hpp"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Window.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <bits/chrono.h>
#define GLM_ENABLE_EXPERIMENTAL false
#include "glm/gtx/string_cast.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar* message, const void* userParam) {
    // Filter specific message types if needed (for example, only errors)
    if (type == GL_DEBUG_TYPE_ERROR) {
        std::cerr << "OpenGL ERROR: " << message << std::endl;
    }
    else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
        std::cerr << "OpenGL DEPRECATED: " << message << std::endl;
    }
    else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) {
        std::cerr << "OpenGL UNDEFINED: " << message << std::endl;
    }
    else if (type == GL_DEBUG_TYPE_PORTABILITY) {
        std::cerr << "OpenGL PORTABILITY: " << message << std::endl;
    }
    else if (type == GL_DEBUG_TYPE_PERFORMANCE) {
        std::cerr << "OpenGL PERFORMANCE: " << message << std::endl;
    }
    else {
        std::cerr << "OpenGL: " << message << std::endl;
    }

    // Optionally, you could also handle warnings differently or just log everything
    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        std::cerr << "High severity error!" << std::endl;
    }
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
        std::cerr << "Medium severity warning!" << std::endl;
    }
    else if (severity == GL_DEBUG_SEVERITY_LOW) {
        std::cerr << "Low severity issue." << std::endl;
    }
}

Game::Game(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        throw std::runtime_error{"Error initializing glfw"};
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_window = new Window{title, width, height};
    glfwMakeContextCurrent(m_window->get_window());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error{"Error settings GL Loader\n"};
    }

    // This sucks
    m_window->init_viewport();
}

void Game::run() {
    constexpr auto rect_width = 0.2f;
    constexpr auto rect_height = 1.0f;

    constexpr auto cube_width = 0.2f;
    constexpr auto cube_height = 0.2f;

    std::vector rect_vertices{
        -0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,

        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,

        -0.1f, 0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, -0.5f, 0.1f, 0.5f,

        0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,

        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,

        -0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, -0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
    };

    std::vector square_vertices{
        -0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,

        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,

        -0.1f, 0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 0.1f, 1.0f,

        0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,

        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,

        -0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
    };

    VertexArray rect_vao;
    VertexArray cube_vao;

    rect_vao.bind();
    VertexBuffer rect_vbo{rect_vertices, 4};
    rect_vbo.set_attrib_pointer<float>(3, 0);
    rect_vbo.set_attrib_pointer<float>(1, 3);

    cube_vao.bind();
    VertexBuffer cube_vbo{square_vertices, 4};
    cube_vbo.set_attrib_pointer<float>(3, 0);
    cube_vbo.set_attrib_pointer<float>(1, 3);

    Shader shader{"../src/vert.glsl", "../src/frag.glsl"};

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    glm::vec3 player_pos{-1.0f, 0.0f, 0.0f};
    glm::vec3 opponent_pos{1.0f, 0.5f, 0.0f};
    glm::vec3 cube_pos{0.0f, 0.0f, 0.0f};
    glm::vec2 cube_vel{0.01f, 0.01f};
    bool test = false;
    unsigned int player_score = 0;
    unsigned int opponent_score = 0;

    while (!glfwWindowShouldClose(m_window->get_window())) {
        if (glfwGetKey(m_window->get_window(), GLFW_KEY_UP) == GLFW_PRESS) {
            player_pos.y = std::min(player_pos.y + 0.01f, 1.0f);
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            player_pos.y = std::max(player_pos.y - 0.01f, -1.0f);
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_W) == GLFW_PRESS) {
            opponent_pos.y = std::min(opponent_pos.y + 0.01f, 1.0f);
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_S) == GLFW_PRESS) {
            opponent_pos.y = std::max(opponent_pos.y - 0.01f, -1.0f);
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        rect_vao.bind();

        glm::mat4 model{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, player_pos);
        shader.set_uniform("model", model);

        glm::mat4 view{1.0f};
        view = glm::translate(view, {0.0f, 0.0f, -3.0f});
        shader.set_uniform("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_window->get_width()) / static_cast<float>(m_window->get_height()), 0.1f, 100.0f);
        shader.set_uniform("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, opponent_pos);
        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        cube_vao.bind();

        if (test) {
            cube_pos += glm::vec3{cube_vel.x, cube_vel.y, 0.0f};
            cube_pos.x = std::min(cube_pos.x, 1.5f);
        } else {
            cube_pos += glm::vec3{cube_vel.x, cube_vel.y, 0.0f};
            cube_pos.x = std::max(cube_pos.x, -1.5f);
        }

        if (cube_pos.x >= 1.5f) {
            player_score++;
            cube_pos = {0.0f, 0.0f, 0.0f};
        } else if (cube_pos.x <= -1.5f) {
            opponent_score++;
            cube_pos = {0.0f, 0.0f, 0.0f};
        }

        if (
                player_pos.x < cube_pos.x + cube_width &&
                player_pos.x + rect_width > cube_pos.x &&
                player_pos.y < cube_pos.y + cube_height + 0.4f &&
                player_pos.y + rect_height > cube_pos.y - 0.4f
            ) {
            std::cout << "Collided with player" << std::endl;
            test = true;
            cube_vel *= -1;
        }

        if (
                opponent_pos.x < cube_pos.x + cube_width &&
                opponent_pos.x - rect_width < cube_pos.x &&
                opponent_pos.y < cube_pos.y + cube_height + 0.4f &&
                opponent_pos.y + rect_height > cube_pos.y - 0.4f
            ) {
            std::cout << "Collided with opponent" << std::endl;
            test = false;
            cube_vel *= -1;
        }

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, cube_pos);
        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        std::cout << "Player position: " << glm::to_string(player_pos) << "\n"
                    << "Square position: " << glm::to_string(cube_pos) << "\n" << std::endl;

        glfwSwapBuffers(m_window->get_window());

        glfwPollEvents();
    }

    std::cout << "Player score: " << player_score << "\n"
                << "Opponent score: " << opponent_score << std::endl;
}

Game::~Game() {
    delete m_window;
    glfwTerminate();
}

