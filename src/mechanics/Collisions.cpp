// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Collisions.cpp
// Collisions checks in x and in y if the player collide with a block and
// if he can dig it.
//
// Author: Sytten
// Creation date: 10/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Collisions.h"
#include "../character/Character.h"
#include "../mapping/TilesMap.h"

Collisions::CollisionType Collisions::collidedX(sf::Rect<float> const& characterRect, int const& digPower, TilesMap const& tilesMap, sf::Vector2i &blockPos)
{
// Check if the player is out of the screen
    if(characterRect.left < 0 || (characterRect.left + characterRect.width) > tilesMap.m_worldSize.x)
        return Collisions::Collision;

m_impact = Collisions::NoCollision;

// Find which tiles are touched by the player
    m_xmin = characterRect.left / tilesMap.m_tileSize.x;
    m_xmax = (characterRect.left + characterRect.width) / tilesMap.m_tileSize.x;
    m_ymin = characterRect.top / tilesMap.m_tileSize.y;
    m_ymax = (characterRect.top + characterRect.height) / tilesMap.m_tileSize.y;

// If the player is on the limit, don't count the tile
    if((int)(characterRect.top + characterRect.height) % tilesMap.m_tileSize.y == 0)
        m_ymax--;

    if((int)(characterRect.left + characterRect.width) % tilesMap.m_tileSize.x == 0)
        m_xmax--;

// Check each tile
    for(int x = m_xmin; x <= m_xmax; ++x)
    {
        for(int y = m_ymin; y <= m_ymax; ++y)
        {
            // Check if we can walk on the tile
                m_result = tilesMap.getTileProp(tilesMap.m_world[x][y]).walkable;

            // If we can't set m_impact to Collision
                if(!m_result)
                    m_impact = Collisions::Collision;

            // Then check if we can dig it
                m_result2 = tilesMap.getTileProp(tilesMap.m_world[x][y]).diggable;
                m_hardness = tilesMap.getTileProp(tilesMap.m_world[x][y]).hardness;

                if(m_result2 && m_hardness <= digPower)
                {
                    m_impact = Collisions::Collision; // Because we collided even if we don't dig

                    // Create the tile rectangle
                        m_tileRect.left = x*tilesMap.m_tileSize.x;
                        m_tileRect.top = y*tilesMap.m_tileSize.y;
                        m_tileRect.width = tilesMap.m_tileSize.x;
                        m_tileRect.height = tilesMap.m_tileSize.y;

                    // Calculate the intersection
                        characterRect.intersects(m_tileRect, m_intersection);

                    // If we are at least at 50% on the tile, we can dig it
                        if(m_intersection.height >= (characterRect.height/2))
                        {
                            blockPos.x = m_tileRect.left;
                            blockPos.y = m_tileRect.top;

                            return Collisions::Diggable;
                        }

                }
        }
    }

return m_impact;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Collisions::CollisionType Collisions::collidedY(sf::Rect<float> const& characterRect,  int const& digPower, TilesMap const& tilesMap, sf::Vector2i &blockPos)
{
// Check if the player is out of the screen
    if((characterRect.top) < 0 || (characterRect.top + characterRect.height) > tilesMap.m_worldSize.y)
        return Collisions::Collision;

m_impact = NoCollision;

// Find which tiles are touched by the player
    m_xmin = characterRect.left / tilesMap.m_tileSize.x;
    m_xmax = (characterRect.left + characterRect.width) / tilesMap.m_tileSize.x;
    m_ymin = characterRect.top / tilesMap.m_tileSize.y;
    m_ymax = (characterRect.top + characterRect.height) / tilesMap.m_tileSize.y;

// If the player is on the limit, don't count the tile
    if((int)(characterRect.top + characterRect.height) % tilesMap.m_tileSize.y == 0)
        m_ymax--;

    if((int)(characterRect.left + characterRect.width) % tilesMap.m_tileSize.x == 0)
        m_xmax--;

// Check each tile
    for(int y = m_ymin; y <= m_ymax; ++y)
    {
        for(int x = m_xmin; x <= m_xmax; ++x)
        {
            // Check if we can walk on the tile
                m_result = tilesMap.getTileProp(tilesMap.m_world[x][y]).walkable;

            // Then check if we can dig it
                m_result2 = tilesMap.getTileProp(tilesMap.m_world[x][y]).diggable;
                m_hardness = tilesMap.getTileProp(tilesMap.m_world[x][y]).hardness;

            // If we can't walk on it set m_impact to Collision
                if(!m_result)
                {
                    m_impact = Collisions::BlockCollision;

                    // Create the tile rectangle
                        m_tileRect.left = x*tilesMap.m_tileSize.x;
                        m_tileRect.top = y*tilesMap.m_tileSize.y;
                        m_tileRect.width = tilesMap.m_tileSize.x;
                        m_tileRect.height = tilesMap.m_tileSize.y;

                    // Calculate the intersection
                        characterRect.intersects(m_tileRect, m_intersection);

                    // If we are at least at 50% on the tile, we can dig it and we can dig it, set m_impact to diggable
                        if(m_intersection.width >= (characterRect.width/2) && m_result2 && m_hardness <= digPower)
                        {
                            blockPos.x = m_tileRect.left;
                            blockPos.y = m_tileRect.top;

                            return Collisions::Diggable;
                        }

                    // If we are at least at 50% on the tile, but we can't dig it
                        else if(m_intersection.width >= (characterRect.width/2))
                        {
                            blockPos.x = m_tileRect.left;
                            blockPos.y = m_tileRect.top;
                        }
                }
        }
    }

return m_impact;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned Collisions::collidedBuilding(sf::Rect<float> const& characterRect, TilesMap const& tilesMap)
{
// Find which tiles are touched by the player
    m_xmin = characterRect.left / tilesMap.m_tileSize.x;
    m_xmax = (characterRect.left + characterRect.width) / tilesMap.m_tileSize.x;
    m_ymin = characterRect.top / tilesMap.m_tileSize.y;
    m_ymax = (characterRect.top + characterRect.height) / tilesMap.m_tileSize.y;

// If the player is on the limit, don't count the tile
    if((int)(characterRect.top + characterRect.height) % tilesMap.m_tileSize.y == 0)
        m_ymax--;

    if((int)(characterRect.left + characterRect.width) % tilesMap.m_tileSize.x == 0)
        m_xmax--;

// Check each tile
    for(int y = m_ymin; y <= m_ymax; ++y)
    {
        for(int x = m_xmin; x <= m_xmax; ++x)
        {
            // Check if the tile is a building and a door
                if(tilesMap.getTileProp(tilesMap.m_world[x][y]).building && tilesMap.getTileProp(tilesMap.m_world[x][y]).door)
                    return tilesMap.getTileProp(tilesMap.m_world[x][y]).buildingID; // If yes, return the ID of the building
        }
    }

    return 0; // Return 0 because no building has been found (and no building have the ID 0)
}
