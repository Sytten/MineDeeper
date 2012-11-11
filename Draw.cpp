#include "Draw.h"

void draw(sf::RenderWindow &window, const Game &game)
{
    //each time we draw the map and the character
    draw(window, game.m_map);
    draw(window, game.m_character);
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
    //set the texture and the position of our character, then draw it
    sf::Sprite robot;
    robot.setTexture(character->characterTexture);
    robot.setPosition(character->x , character->y);
    window.draw(robot);
}

void draw(sf::RenderWindow &window, const MainMenu &mainMenu)
{
    //draw our main menu image
    sf::Sprite image(mainMenu.m_mainMenuImage);
    window.draw(image);
}
