#include "Game.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Window.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/trigonometric.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>
#include <vector>

Game::Game(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        throw std::runtime_error{"Error initializing glfw"};
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
    auto rect_vertices = std::vector{
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

    auto square_vertices = std::vector{
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

    VertexBuffer rect_vbo{rect_vertices, 4};
    rect_vbo.set_attrib_pointer<float>(3, 0);
    rect_vbo.set_attrib_pointer<float>(1, 3);

    VertexArray square_vao;

    VertexBuffer square_vbo{square_vertices, 4};
    square_vbo.set_attrib_pointer<float>(3, 0);
    square_vbo.set_attrib_pointer<float>(1, 3);

    Shader shader{"../src/vert.glsl", "../src/frag.glsl"};
    shader.bind();

    glEnable(GL_DEPTH_TEST);

    float y_pos = 0.0f;
    glm::vec2 square_pos = {0.0f, 0.0f};

    while (!glfwWindowShouldClose(m_window->get_window())) {
        if (glfwGetKey(m_window->get_window(), GLFW_KEY_UP) == GLFW_PRESS) {
            y_pos = std::min(y_pos + 0.01f, 1.0f);
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            y_pos = std::max(y_pos - 0.01f, -1.0f);
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rect_vao.bind();

        glm::mat4 model{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, {-1.0f, y_pos, 0.0f});
        shader.set_uniform("model", model);

        glm::mat4 view{1.0f};
        view = glm::translate(view, {0.0f, 0.0f, -3.0f});
        shader.set_uniform("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_window->get_width()) / static_cast<float>(m_window->get_height()), 0.1f, 100.0f);
        shader.set_uniform("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, {1.0f, 0.0f, 0.0f});
        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        square_vao.bind();

        square_pos += glm::vec2{-0.001f, 0.0f};

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, {square_pos.x, square_pos.y, 0.0f});
        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(m_window->get_window());

        glfwPollEvents();
    }
}

Game::~Game() {
    delete m_window;
    glfwTerminate();
}
