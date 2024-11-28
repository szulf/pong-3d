#pragma once

#include "Window.hpp"
#include <optional>

class Game
{
public:
    Game(const std::string& title, int width, int height);
    ~Game();

    void run();

private:
    // Window* m_window;
    std::optional<Window> m_window;
};
