#include "Game.hpp"
#include <cstdio>
#include <stdexcept>

int main()
{
    try
    {
        Game game{"Pong 3D", 800, 600};
        game.run();
    }
    catch (std::runtime_error e)
    {
        std::printf("%s", e.what());
    }

    return 0;
}
