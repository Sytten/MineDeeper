// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// KeyboardCharacterMover.h
// The header file of the KeyboardCharacterMover object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef CHARACTERMOVER_H
#define CHARACTERMOVER_H

#include <SFML/Graphics.hpp>

#include "Collisions.h"
#include "Physic.h"

class Character;
class TilesMap;
class Camera;
class Background;

class KeyboardCharacterMover
{
    public:
        KeyboardCharacterMover();

        enum Direction{ SOUTH, NORTH, EAST, WEST };

        // Functions to change the directions
            void addDirection(Direction direction);
            void removeDirection(Direction direction);

        // Function to move the character
            void move(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Time elapsedTime);

    private:
        // Function to dig
            void dig(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Vector2i blockPos, Direction digDirection);

        // The directions
            bool m_south;
            bool m_north;
            bool m_east;
            bool m_west;

        // Variables for the collisions checking
            Collisions m_collisions;
            Collisions::CollisionType m_result;

        // So we don't recreate them each time we move the character
            sf::Vector2i m_blockPos; // The block that we're going to dig
            sf::Rect<float> m_testRect;
            Physic m_physic;
            bool m_flying;

};
#endif
