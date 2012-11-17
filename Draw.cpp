#include "Draw.h"

void draw(sf::RenderWindow &window, const Game &game)
{
    //each time we draw the background, the tiles map and the character
    sf::Sprite background;
    background.setTexture(game.m_background);
    background.setScale(0.5, 0.5);
    window.draw(background);

    draw(window, game.m_tilesMap);
    draw(window, game.m_character);
}

void draw(sf::RenderWindow &window, const TilesMap &tilesMap)
{
    sf::Sprite tile;
    tile.setTexture(tilesMap.m_tileSet);

    for(int x(0); x < tilesMap.m_worldWidth/tilesMap.m_tileWidth; x++) //check each number of the vector
    {
        for(int y(0); y < tilesMap.m_worldHeight/tilesMap.m_tileHeight; y++)
        {
            if(tilesMap.table[y*(tilesMap.m_worldWidth/tilesMap.m_tileWidth)+x] == 1) //if 1 draw land
            {
                tile.setTextureRect(tilesMap.getTileProp(1).tileRect);
                tile.setPosition(x*75, y*75);

                window.draw(tile);
            }

            if(tilesMap.table[y*(tilesMap.m_worldWidth/tilesMap.m_tileWidth)+x] == 2) //if 2 draw background land
            {
                tile.setTextureRect(tilesMap.getTileProp(2).tileRect);
                tile.setPosition(x*75, y*75);

                window.draw(tile);
            }
        }
    }
}

void draw(sf::RenderWindow &window, const Character &character)
{
    //set the texture and the position of our character, then draw it
    sf::Sprite robot;
    robot.setTexture(character.characterTexture);
    robot.setPosition(character.characterRect.left , character.characterRect.top);
    window.draw(robot);
}

void draw(sf::RenderWindow &window, const MainMenu &mainMenu)
{
    //draw our main menu image
    sf::Sprite image(mainMenu.m_mainMenuImage);
    window.draw(image);
}
