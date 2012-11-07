#include <SFML/Graphics.hpp>
#include "Map.h"

#define WIDTH_TILE 75
#define HEIGHT_TILE 75

#define NBR_TILES_WIDTH 11
#define NBR_TILES_HEIGHT 10

int main()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(825, 750), "MineDeeper", sf::Style::Close);
    Map gameMap(NBR_TILES_WIDTH, NBR_TILES_HEIGHT);
    gameMap.createMap();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        gameMap.drawMap(window);
        window->display();
    }

    delete window;

    return 0;
}
