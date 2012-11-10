#include "CharacterMover.h"
#include "Character.h"

CharacterMover::CharacterMover() : _north(false), _south(false), _west(false), _east(false)
{
}

void CharacterMover::addDirection(Direction direction)
{
    switch(direction)
    {
        case NORTH:
            _north = true;
            break;

        case SOUTH:
            _south = true;
            break;

        case EAST:
            _east = true;
            break;

        case WEST:
            _west = true;
            break;
    }
}

void CharacterMover::removeDirection(Direction direction)
{
    switch(direction)
    {
        case NORTH:
            _north = false;
            break;

        case SOUTH:
            _south = false;
            break;

        case EAST:
            _east = false;
            break;

        case WEST:
            _west = false;
            break;
    }
}

void CharacterMover::move(Character *character)
{
    if(_north == true)
    {
        character->y -= character->speed;
    }

    if(_south == true)
    {
        character->y += character->speed;
    }

    if(_east == true)
    {
        character->x += character->speed;
    }

    if(_west ==  true)
    {
        character->x -= character->speed;
    }
}
