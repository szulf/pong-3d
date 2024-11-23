#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

Window::Window(const std::string& title, int width, int height) : m_width{width}, m_height{height}, m_title{title}
{
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        throw std::runtime_error{"Error creating window"};
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

void Window::init_viewport()
{
    glViewport(0, 0, m_width, m_height);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
