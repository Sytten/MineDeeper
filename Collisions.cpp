#include "Collisions.h"
#include "Character.h"
#include "TilesMap.h"

bool Collisions::collidedX(sf::Rect<float> const& characterRect, TilesMap const& tilesMap)
{
    if(characterRect.left < 0 || (characterRect.left + characterRect.width) > tilesMap.m_worldSize.x)
        return true;

    if(collidedDecor(characterRect, tilesMap))
        return true;

    return false;
}


bool Collisions::collidedY(sf::Rect<float> const& characterRect, TilesMap const& tilesMap)
{
    if((characterRect.top) < 0 || (characterRect.top + characterRect.height) > tilesMap.m_worldSize.y)
        return true;

    if(collidedDecor(characterRect, tilesMap))
        return true;

    return false;
}


bool Collisions::collidedDecor(sf::Rect<float> const& characterRect, TilesMap const& tilesMap)
{
    int xmin = characterRect.left / tilesMap.m_tileSize.x;
    int xmax = (characterRect.left + characterRect.width - 1) / tilesMap.m_tileSize.x;
    int ymin = characterRect.top / tilesMap.m_tileSize.y;
    int ymax = (characterRect.top + characterRect.height - 1) / tilesMap.m_tileSize.y;

    for(int x = xmin; x <= xmax; x++)
    {
        for(int y = ymin; y <= ymax; y++)
        {
            bool result = tilesMap.getTileProp(tilesMap.m_world[x][y]).walkable;
            if(!result)
                return true;
        }
    }

    return false;
}
