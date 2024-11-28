#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <memory>
#include <stdexcept>

Window::Window(const std::string& title, int width, int height) : m_window{glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), glfwDestroyWindow}, m_width{width}, m_height{height}, m_title{title}
{
    if (!m_window) {
        throw std::runtime_error{"Error creating window"};
    }
}

Window::Window(Window&& other) noexcept : m_window{std::move(other.m_window)}, m_width{std::move(other.m_width)}, m_height{std::move(other.m_height)}, m_title{std::move(other.m_title)} {}

Window& Window::operator=(Window&& other) noexcept
{
    if (this != &other)
    {
        m_window = std::move(other.m_window);
        m_title = std::move(other.m_title);
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
    }

    return *this;
}

void Window::init_viewport()
{
    glViewport(0, 0, m_width, m_height);
    glfwSetFramebufferSizeCallback(m_window.get(), framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
