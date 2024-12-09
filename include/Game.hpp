#pragma once

#include "Renderer.hpp"
#include "Window.hpp"
#include <optional>

class Game
{
public:
    Game(const std::string& title, int width, int height);
    ~Game();

    auto run() -> void;

private:
    std::optional<Window> m_window;
    std::optional<Renderer> m_renderer;
};
