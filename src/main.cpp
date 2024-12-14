#include "Game.hpp"
#include <iostream>

int main()
{
    try
    {
        Game game{"Pong 3D", 800, 600};
        game.run();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what();
    }

    return 0;
}
