#include "Collisions.h"
#include "Character.h"
#include "TilesMap.h"

Collisions::CollisionType Collisions::collidedX(sf::Rect<float> const& characterRect, TilesMap const& tilesMap, sf::Vector2i &blockPos)
{
    if(characterRect.left < 0 || (characterRect.left + characterRect.width) > tilesMap.m_worldSize.x)
        return Collisions::Collision;

    sf::Rect<float> tileRect;
    sf::Rect<float> intersection;
    CollisionType impact(NoCollision);

    m_xmin = characterRect.left / tilesMap.m_tileSize.x;
    m_xmax = (characterRect.left + characterRect.width) / tilesMap.m_tileSize.x;
    m_ymin = characterRect.top / tilesMap.m_tileSize.y;
    m_ymax = (characterRect.top + characterRect.height) / tilesMap.m_tileSize.y;

    if((int)(characterRect.top + characterRect.height) % tilesMap.m_tileSize.y == 0)
        m_ymax--;

    if((int)(characterRect.left + characterRect.width) % tilesMap.m_tileSize.x == 0)
        m_xmax--;

    for(int x = m_xmin; x <= m_xmax; x++)
    {
        for(int y = m_ymin; y <= m_ymax; y++)
        {
            bool result = tilesMap.getTileProp(tilesMap.m_world[x][y]).walkable; //check if we can go on the tile
            int test = tilesMap.m_world[x][y];
            if(!result) //if not, then check if we can dig it
            {
                impact = Collisions::Collision;
                tileRect.left = x*tilesMap.m_tileSize.x;
                tileRect.top = y*tilesMap.m_tileSize.y;
                tileRect.width = tilesMap.m_tileSize.x;
                tileRect.height = tilesMap.m_tileSize.y;

                characterRect.intersects(tileRect, intersection);

                if(intersection.height >= (characterRect.height/2))
                {
                    blockPos.x = tileRect.left;
                    blockPos.y = tileRect.top;

                    return Collisions::Diggable;
                }

            }
        }
    }

    return impact;
}


Collisions::CollisionType Collisions::collidedY(sf::Rect<float> const& characterRect, TilesMap const& tilesMap, sf::Vector2i &blockPos)
{
    if((characterRect.top) < 0 || (characterRect.top + characterRect.height) > tilesMap.m_worldSize.y)
        return Collisions::Collision;

    sf::Rect<float> tileRect;
    sf::Rect<float> intersection;
    CollisionType impact(NoCollision);

    m_xmin = characterRect.left / tilesMap.m_tileSize.x;
    m_xmax = (characterRect.left + characterRect.width) / tilesMap.m_tileSize.x;
    m_ymin = characterRect.top / tilesMap.m_tileSize.y;
    m_ymax = (characterRect.top + characterRect.height) / tilesMap.m_tileSize.y;

    if((int)(characterRect.top + characterRect.height) % tilesMap.m_tileSize.y == 0)
        m_ymax--;

    if((int)(characterRect.left + characterRect.width) % tilesMap.m_tileSize.x == 0)
        m_xmax--;

    for(int y = m_ymin; y <= m_ymax; y++)
    {
        for(int x = m_xmin; x <= m_xmax; x++)
        {
            bool result = tilesMap.getTileProp(tilesMap.m_world[x][y]).walkable; //check if we can go on the tile
            if(!result) //if not, then check if we can dig it
            {
                impact = Collisions::Collision;
                tileRect.left = x*tilesMap.m_tileSize.x;
                tileRect.top = y*tilesMap.m_tileSize.y;
                tileRect.width = tilesMap.m_tileSize.x;
                tileRect.height = tilesMap.m_tileSize.y;

                characterRect.intersects(tileRect, intersection);

                if(intersection.width >= (characterRect.width/2))
                {
                    blockPos.x = tileRect.left;
                    blockPos.y = tileRect.top;

                    return Collisions::Diggable;
                }

            }
        }
    }

    return impact;
}
