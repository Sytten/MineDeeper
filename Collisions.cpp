#include "Collisions.h"
#include "Character.h"
#include "TilesMap.h"

bool Collisions::collidedX(sf::Rect<float> const& characterRect, TilesMap &tilesMap)
{
    if(characterRect.left < 0 || (characterRect.left + characterRect.width) > tilesMap.m_worldWidth)
        return true;

    if(collidedDecor(characterRect, tilesMap))
        return true;

    return false;
}


bool Collisions::collidedY(sf::Rect<float> const& characterRect, TilesMap &tilesMap)
{
    if((characterRect.top) < 0 || (characterRect.top + characterRect.height) > tilesMap.m_worldHeight)
        return true;

    if(collidedDecor(characterRect, tilesMap))
        return true;

    return false;
}


bool Collisions::collidedDecor(sf::Rect<float> const& characterRect, TilesMap &tilesMap)
{
    sf::Rect<float> rectTest;
        rectTest.height = tilesMap.m_tileHeight;
        rectTest.width = tilesMap.m_tileWidth;

    for(int x(0); x < tilesMap.m_worldWidth/tilesMap.m_tileWidth; x++)
    {
        for(int y(0); y < tilesMap.m_worldHeight/tilesMap.m_tileHeight; y++)
        {
            int tileIndex = tilesMap.table[y*(tilesMap.m_worldWidth/tilesMap.m_tileWidth)+x];
            if(tilesMap.getTileProp(tileIndex).full)
            {
                rectTest.top = y*tilesMap.m_tileHeight;
                rectTest.left =  x*tilesMap.m_tileWidth;

                if(characterRect.intersects(rectTest))
                    return true;
            }
        }
    }

    return false;
}
