#include "CharacterMover.h"
#include "Character.h"

CharacterMover::CharacterMover() : m_north(false), m_south(false), m_west(false), m_east(false) //set them all to false (security)
{
}

void CharacterMover::addDirection(Direction direction)
{
    switch(direction) //set the given direction to true, so we can move our character
    {
        case NORTH:
            m_north = true;
            break;

        case SOUTH:
            m_south = true;
            break;

        case EAST:
            m_east = true;
            break;

        case WEST:
            m_west = true;
            break;
    }
}

void CharacterMover::removeDirection(Direction direction) //set the given direction to false, so we don't move our character
{
    switch(direction)
    {
        case NORTH:
            m_north = false;
            break;

        case SOUTH:
            m_south = false;
            break;

        case EAST:
            m_east = false;
            break;

        case WEST:
            m_west = false;
            break;
    }
}

void CharacterMover::move(Character *character)
{
    //check each direction, if it's set to true, move the character in this direction
    if(m_north == true)
    {
        character->y -= character->speed;
    }

    if(m_south == true)
    {
        character->y += character->speed;
    }

    if(m_east == true)
    {
        character->x += character->speed;
    }

    if(m_west ==  true)
    {
        character->x -= character->speed;
    }
}
