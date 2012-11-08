#include "Draw.h"

void draw(sf::RenderWindow &window, const Game &game)
{
    draw(window, game.map);
    draw(window, game.character);
}

void draw(sf::RenderWindow &window, const Map *map)
{
    sf::Sprite tile;

    for(int x(0); x < map->m_nbrTilesWidth; x++) //check each number of the vector
    {
        for(int y(0); y < map->m_nbrTilesHeight; y++)
        {

            if(map->table[y*map->m_nbrTilesWidth+x] == 0) //if 0 draw sky
            {
                tile.setTexture(map->sky);
                tile.setPosition(x*75, y*75);

                window.draw(tile);
            }

            if(map->table[y*map->m_nbrTilesWidth+x] == 1) //if 1 draw land
            {
                tile.setTexture(map->land);
                tile.setPosition(x*75, y*75);

                window.draw(tile);
            }
        }
    }
}

void draw(sf::RenderWindow &window, const Character *character)
{
    sf::Sprite robot;
    robot.setTexture(character->characterTexture);
    robot.setPosition(character->x , character->y);
    window.draw(robot);
}
