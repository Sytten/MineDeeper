// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 18/02/2013
// ---------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include "Game.h"

#include <iostream>

int main()
{
    //try the following code
    try
    {
        Game game; //create our map object
        game.gameLoop(); //start the game
    }
    //handle errors
    catch(std::exception &e)
    {
        std::cerr << "An exception occurred : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "An unexpected exception occurred !" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
