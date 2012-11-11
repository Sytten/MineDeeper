#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Draw.h"
#include "CharacterMover.h"
#include "Collisions.h"

int main()
{
    //define the tiles of the game
    const unsigned int WIDTH_TILE = 75; /**************Need to use it in the futur*****************/
    const unsigned int HEIGHT_TILE = 75; /**************Need to use it in the futur*****************/
    const unsigned int NBR_TILES_WIDTH = 11;
    const unsigned int NBR_TILES_HEIGHT = 10;

    Game game(NBR_TILES_WIDTH, NBR_TILES_HEIGHT); //create our pointers map, character and character mover
    game.start();

    return EXIT_SUCCESS;
}
