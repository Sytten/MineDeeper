#include "Draw.h"
#include <iostream>
#include <cmath>

void draw(sf::RenderWindow &window, Game &game)
{
    //each time we draw the background, the tiles map and the character
    draw(window, game.m_background);
    draw(window, game.m_tilesMap, game.m_camera);
    draw(window, game.m_character, game.m_camera.getPosition());
}

void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera)
{
    tilesMap.m_camOffSet = camera.getOffset(tilesMap.m_tileSize);
    tilesMap.m_bounds = camera.getBounds(tilesMap.m_tileSize, tilesMap.m_worldSize);
    sf::Vector2f test = camera.getPosition();

    for(int y = 0, tileY = tilesMap.m_bounds.top; y < tilesMap.m_bounds.height; y++, tileY++)
    {
        for(int x = 0, tileX = tilesMap.m_bounds.left; x < tilesMap.m_bounds.width; x++, tileX++)
        {
                tilesMap.m_tile.setTextureRect(tilesMap.getTileProp(tilesMap.m_world[tileX][tileY]).posInTileSet);
                tilesMap.m_tile.setPosition((x * tilesMap.m_tileSize.x) - tilesMap.m_camOffSet.x, (y * tilesMap.m_tileSize.y) - tilesMap.m_camOffSet.y);

                window.draw(tilesMap.m_tile);
        }
    }

}

void draw(sf::RenderWindow &window, Character &character, sf::Vector2f cameraPos)
{
    //set the position on the screen
    character.setCharacterPosition(character.getCharacterRect().left - cameraPos.x, character.getCharacterRect().top - cameraPos.y);
    window.draw(character.getCharacterSprite());
}

void draw(sf::RenderWindow &window, const MainMenu &mainMenu)
{
    //draw our main menu image
    window.draw(mainMenu.getMainMenuSprite());
}

void draw(sf::RenderWindow &window, const Background &background)
{
    window.draw(background.getBackgroundSprite());
}
