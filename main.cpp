#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Draw.h"

#define WIDTH_TILE 75 //the size of my squares
#define HEIGHT_TILE 75

#define NBR_TILES_WIDTH 11 //the number of squares in my window
#define NBR_TILES_HEIGHT 10

int main()
{
    //Create basic window and create our map
    sf::RenderWindow window(sf::VideoMode(825, 750), "MineDeeper", sf::Style::Close);
    Game game(NBR_TILES_WIDTH, NBR_TILES_HEIGHT);
    game.createMap();

    bool playing = true;

    sf::Event event;

    //Start game loop
    while (playing)
    {
        while (window.pollEvent(event)) //check the events
        {
            if (event.type == sf::Event::Closed) //if the player want to quit
                playing = false;
        }

        window.clear();
        draw(window, game);
        window.display();
    }

    return 0;
}
