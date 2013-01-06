#ifndef CHARACTERMOVER_H
#define CHARACTERMOVER_H

#include <SFML/Graphics.hpp>

#include "Collisions.h"

class Character;
class TilesMap;
class Camera;
class Background;

class KeyboardCharacterMover
{
    public:
        KeyboardCharacterMover();

        enum Direction{ SOUTH, NORTH, EAST, WEST };

        void addDirection(Direction direction);
        void removeDirection(Direction direction);
        void move(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Time elapsedTime);

    private:
        void dig(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Vector2i blockPos, Direction digDirection);

        bool m_south;
        bool m_north;
        bool m_east;
        bool m_west;

        Collisions m_collisions;
        Collisions::CollisionType m_result;
        sf::Vector2i m_blockPos; //the block who's going to be digged
        sf::Rect<float> m_testRect;

};
#endif
