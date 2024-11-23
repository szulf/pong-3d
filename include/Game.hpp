#pragma once

#include "Window.hpp"

class Game
{
public:
    Game(const std::string& title, int width, int height);
    ~Game();

    void run();

private:
    Window* m_window;
};
