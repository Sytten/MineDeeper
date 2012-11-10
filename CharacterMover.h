#ifndef CHARACTERMOVER_H
#define CHARACTERMOVER_H

#include <SFML/Graphics.hpp>

class Character;

enum Direction
{
    NONE,
    SOUTH,
    NORTH,
    EAST,
    WEST
};

class CharacterMover
{
    public:
    CharacterMover();
    void addDirection(Direction direction);
    void removeDirection(Direction direction);
    void move(Character *character);

    private:
    bool _south;
    bool _north;
    bool _east;
    bool _west;

};
#endif
