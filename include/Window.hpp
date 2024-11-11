#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    auto get_window() -> GLFWwindow* {
        return m_window;
    }

    auto get_title() -> const std::string& {
        return m_title;
    }

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};
