#include "Game.hpp"
#include "Window.hpp"
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
    while (!glfwWindowShouldClose(m_window->get_window())) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_window->get_window());

        glfwPollEvents();
    }
}

Game::~Game() {
    delete m_window;
    glfwTerminate();
}
