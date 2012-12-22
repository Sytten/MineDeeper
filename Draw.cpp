#include "Draw.h"
#include <iostream>
#include <cmath>

void draw(sf::RenderWindow &window, const Game &game)
{
    //each time we draw the background, the tiles map and the character
    sf::Sprite background;
    background.setTexture(game.m_background);
    background.setScale(0.5, 0.5);
    window.draw(background);

    draw(window, game.m_tilesMap, game.m_camera);
    draw(window, game.m_character, game.m_camera.getPosition());
}

void draw(sf::RenderWindow &window, const TilesMap &tilesMap, const Camera &camera)
{
    sf::Vector2<int> camOffSet = camera.getOffset(tilesMap.m_tileSize);
    sf::Rect<int> bounds = camera.getBounds(tilesMap.m_tileSize);

    sf::Sprite tile;
    tile.setTexture(tilesMap.m_tileSet);

    for(int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++)
    {
        for(int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++)
        {
                tile.setTextureRect(tilesMap.getTileProp(tilesMap.m_world[tileX][tileY]).posInTileSet);
                tile.setPosition((x * tilesMap.m_tileSize.x) - camOffSet.x, (y * tilesMap.m_tileSize.y) - camOffSet.y);

                window.draw(tile);
        }
    }

}

void draw(sf::RenderWindow &window, const Character &character, sf::Vector2f cameraPos)
{
    //set the texture of the character
    sf::Sprite spriteCharacter;
    spriteCharacter.setTexture(character.characterTexture);

    //set the position on the screen
    spriteCharacter.setPosition(character.characterRect.left - cameraPos.x, character.characterRect.top - cameraPos.y);
    window.draw(spriteCharacter);
}

void draw(sf::RenderWindow &window, const MainMenu &mainMenu)
{
    //draw our main menu image
    sf::Sprite image(mainMenu.m_mainMenuImage);
    window.draw(image);
}
