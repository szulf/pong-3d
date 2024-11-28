#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

class Window
{
public:
    Window(const std::string& title, int width, int height);
    ~Window() = default;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    auto get_window() -> GLFWwindow*
    {
        return m_window.get();
    }

    auto get_title() const -> const std::string&
    {
        return m_title;
    }

    // Width and Height seem stupid, bc they should be const, but can't because of this get size function
    auto get_width() -> int
    {
        glfwGetFramebufferSize(m_window.get(), &m_width, &m_height);
        return m_width;
    }

    auto get_height() -> int
    {
        glfwGetFramebufferSize(m_window.get(), &m_width, &m_height);
        return m_height;
    }

    void init_viewport();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> m_window;

    int m_width;
    int m_height;
    std::string m_title;
};
