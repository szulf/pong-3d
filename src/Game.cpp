#include "Game.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include <array>
#include <stdexcept>

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
}

void Game::run() {
    auto vertices = std::to_array({
        -0.1f, -0.5f, 0.5f,
        -0.1f, 0.5f, 0.5f,
        0.1f, -0.5f, 0.5f,

        -0.1f, 0.5f, 0.5f,
        0.1f, -0.5f, 0.5f,
        0.1f, 0.5f, 0.5f,
    });

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shader{"../src/vert.glsl", "../src/frag.glsl"};
    shader.bind();

    while (!glfwWindowShouldClose(m_window->get_window())) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(m_window->get_window());

        glfwPollEvents();
    }
}

Game::~Game() {
    delete m_window;
    glfwTerminate();
}
