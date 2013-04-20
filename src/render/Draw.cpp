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
#include "../character/Life.h"

void draw(sf::RenderWindow &window, Game &game)
{
    // Each time we draw the background, the map and the character
        draw(window, *(game.m_background));
        draw(window, *(game.m_tilesMap), *(game.m_camera));
        draw(window, *(game.m_character), game.m_camera->getPosition(), game.m_tilesMap->getTileSize());

    //
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

void draw(sf::RenderWindow &window, Character &character, sf::Vector2f cameraPos, sf::Vector2i tileSize)
{
    // Set the position on the screen
        character.verifyOffset();
        character.setCharacterPosition(character.m_characterRect.left - cameraPos.x + character.m_drawOffset.x, character.getCharacterRect().top - cameraPos.y + character.m_drawOffset.y);

    // Run the filter to make changes and draw it if active
        if(character.m_damagesFilter.isActive())
        {
            character.m_damagesFilter.runFilter();
            window.draw(character.m_damagesFilter.getFilter());
        }

    // Draw the life and the fuel bars
        window.draw(character.m_life.getFullLifeBarSprite());
        window.draw(character.m_life.getShapeLifeBarSprite());
        window.draw(character.m_fuel.getFullFuelBarSprite());
        window.draw(character.m_fuel.getShapeFuelBarSprite());

    // Update the texts, delete them if necessary or draw them
        for(character.m_i = 0; character.m_i < character.m_floatingTexts.size(); ++(character.m_i))
        {
            if(character.m_floatingTexts.at(character.m_i)->isFinished())
                character.m_floatingTexts.erase(character.m_floatingTexts.begin() + character.m_i);
            else
            {
                character.m_floatingTexts.at(character.m_i)->update();
                window.draw(character.m_floatingTexts.at(character.m_i)->getText(cameraPos));
            }
        }

    // Draw the altitude
        character.verifyAltitude(tileSize);
        window.draw(character.m_altitude);

    // Draw the character
        window.draw(character.m_characterSprite);
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
