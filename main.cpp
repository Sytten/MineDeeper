// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 26/01/2013
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
        game.start(); //start the initializer et the game after
    }
    //handle errors
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
