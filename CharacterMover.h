#ifndef CHARACTERMOVER_H
#define CHARACTERMOVER_H

#include <SFML/Graphics.hpp>

class Character;

class CharacterMover
{
    public:
        CharacterMover();

        enum Direction{ SOUTH, NORTH, EAST, WEST };

        void addDirection(Direction direction);
        void removeDirection(Direction direction);
        void move(Character *character);

    private:
        bool m_south;
        bool m_north;
        bool m_east;
        bool m_west;

};
#endif
