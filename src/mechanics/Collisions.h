// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Collisions.h
// The header file of the Collisions object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 10/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>

class Character;
class TilesMap;

class Collisions
{
    public:
        enum CollisionType{NoCollision, Collision, BlockCollision, Diggable};

        // Functions to check collisions
            CollisionType collidedX(sf::Rect<float> const& characterRect, int const& digPower, TilesMap const& tilesMap, sf::Vector2i &blockPos);
            CollisionType collidedY(sf::Rect<float> const& characterRect, int const& digPower, TilesMap const& tilesMap, sf::Vector2i &blockPos);
            unsigned collidedBuilding(sf::Rect<float> const& characterRect, TilesMap const& tilesMap);

    private:
        // Tiles touched by the player
            int m_xmin;
            int m_xmax;
            int m_ymin;
            int m_ymax;

        // Other variables, so we don`t recreate them each time we call the function
            CollisionType m_impact;
            sf::Rect<float> m_tileRect;
            sf::Rect<float> m_intersection;
            bool m_result;
            bool m_result2;
            int m_hardness;
};

#endif
