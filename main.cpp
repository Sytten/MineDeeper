#include <SFML/Graphics.hpp>
#include "Game.h"

#include <iostream>

int main()
{
    try
    {
        Game game; //create our pointers map, character and character mover
        game.start();
    }
    catch(std::exception &e)
    {
        std::cerr << "An exception occured : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "An unexpected exception occured !" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
