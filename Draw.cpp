// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Draw.cpp
// The draw module draws all the objects in my game (tiles, character,
// main menu, etc.).
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 04/02/2013
// ---------------------------------------------------------------------------

#include "Draw.h"
#include "Life.h"

void draw(sf::RenderWindow &window, Game &game)
{
    // Each time we draw the background, the map and the character
        draw(window, *(game.m_background));
        draw(window, *(game.m_tilesMap), *(game.m_camera));
        draw(window, *(game.m_character), game.m_camera->getPosition());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera)
{
    // Get information about the camera
        tilesMap.m_camOffSet = camera.getOffset(tilesMap.m_tileSize); // Get the offset so we can remove it to the position of the tile on the screen
        tilesMap.m_bounds = camera.getBounds(tilesMap.m_tileSize, tilesMap.m_worldSize); // Get the bounds so we don`t draw all the map

    // Draw each tile
        for(int y = 0, tileY = tilesMap.m_bounds.top; y < tilesMap.m_bounds.height; ++y, ++tileY)
        {
            for(int x = 0, tileX = tilesMap.m_bounds.left; x < tilesMap.m_bounds.width; ++x, ++tileX)
            {
                // Display the good texture
                    tilesMap.m_tile.setTextureRect(tilesMap.getTileProp(tilesMap.m_world[tileX][tileY]).posInTileSet);

                // Find the position on the screen
                    tilesMap.m_tile.setPosition((x * tilesMap.m_tileSize.x) - tilesMap.m_camOffSet.x, (y * tilesMap.m_tileSize.y) - tilesMap.m_camOffSet.y);

                window.draw(tilesMap.m_tile);
            }
        }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw(sf::RenderWindow &window, Character &character, sf::Vector2f cameraPos)
{
    // Set the position on the screen
        character.setCharacterPosition(character.getCharacterRect().left - cameraPos.x, character.getCharacterRect().top - cameraPos.y);

    // Draw the life and the fuel bars
        window.draw(character.getLife().getFullLifeBarSprite());
        window.draw(character.getLife().getShapeLifeBarSprite());
        window.draw(character.getFuel().getFullFuelBarSprite());
        window.draw(character.getFuel().getShapeFuelBarSprite());

    // Draw the character
        window.draw(character.getCharacterSprite());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw(sf::RenderWindow &window, const MainMenu &mainMenu)
{
    // Draw our main menu image at (0,0)
        window.draw(mainMenu.getMainMenuSprite());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw(sf::RenderWindow &window, const Background &background)
{
    // Draw our background image at (0,0)
        window.draw(background.getBackgroundSprite());
}
