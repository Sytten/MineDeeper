#ifndef CHARACTERMOVER_H
#define CHARACTERMOVER_H

#include <SFML/Graphics.hpp>

#include "Collisions.h"

class Character;
class TilesMap;
class Camera;

class KeyboardCharacterMover
{
    public:
        KeyboardCharacterMover();

        enum Direction{ SOUTH, NORTH, EAST, WEST };

        void addDirection(Direction direction);
        void removeDirection(Direction direction);
        void move(Character &character, TilesMap &tilesMap, Camera &camera, sf::Time elapsedTime);

    private:
        bool m_south;
        bool m_north;
        bool m_east;
        bool m_west;

        Collisions m_collisions;
        bool m_result;
        sf::Rect<float> m_testRect;
        sf::Rect<float> m_initialCharacterRect;

};
#endif
