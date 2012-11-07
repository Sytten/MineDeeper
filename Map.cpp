#include "Map.h"

Map::Map(int NbrTilesWidth, int NbrTilesHeight) : m_nbrTilesWidth(NbrTilesWidth), m_nbrTilesHeight(NbrTilesHeight)
{
    sky.loadFromFile("ciel.png");
    land.loadFromFile("terre.png");
}

void Map::createMap()
{
    table.reserve(110);

    for(int i(0); i < 88; i++)
        table.push_back(0);

    for(int i(0); i < 22; i++)
        table.push_back(1);
}

void Map::drawMap(sf::RenderWindow *window)
{
    for(int x(0); x < m_nbrTilesWidth; x++)
    {
        for(int y(0); y < m_nbrTilesHeight; y++)
        {

            if(table[y*m_nbrTilesWidth+x] == 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(sky);
                sprite.setPosition(x*75, y*75);

                window->draw(sprite);
            }

            if(table[y*m_nbrTilesWidth+x] == 1)
            {
                sf::Sprite sprite;
                sprite.setTexture(land);
                sprite.setPosition(x*75, y*75);

                window->draw(sprite);
            }
        }
    }
}
