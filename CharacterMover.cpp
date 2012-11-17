#include "CharacterMover.h"
#include "Character.h"
#include "Collisions.h"
#include "TilesMap.h"

CharacterMover::CharacterMover() : m_south(false), m_north(false), m_east(false), m_west(false) //set them all to false (security)
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

void CharacterMover::move(Character &character, TilesMap &tilesMap, sf::Time elapsedTime)
{
    //if the 2 directions are set to false, then set the velocity to 0
    if(!m_north && !m_south)
        character.m_velocityY = 0;

    if(!m_east && !m_west)
        character.m_velocityX = 0;


    //if one direction is true, add ou delete 3 to the velocity (x or y)
    if(m_north)
        character.m_velocityY -= 3.0f;

    if(m_south)
        character.m_velocityY += 3.0f;

    if(m_east)
        character.m_velocityX += 3.0f;

    if(m_west)
        character.m_velocityX -= 3.0f;


    //check if the velocitys are higher than the max
    if(character.m_velocityX > character.m_maxVelocity)
        character.m_velocityX = character.m_maxVelocity;

    if(character.m_velocityX < -character.m_maxVelocity)
        character.m_velocityX = -character.m_maxVelocity;

    if(character.m_velocityY > character.m_maxVelocity)
        character.m_velocityY = character.m_maxVelocity;

    if(character.m_velocityY < -character.m_maxVelocity)
        character.m_velocityY = -character.m_maxVelocity;


    //check for collisions, if everything is ok: move the character
    Collisions collisions;
    bool result = false;

    sf::Rect<float> testRect = character.characterRect;

    testRect.left += elapsedTime.asSeconds()* character.m_velocityX;
    result = collisions.collidedX(testRect, tilesMap);
    if(!result)
        character.characterRect.left += (character.m_velocityX * elapsedTime.asSeconds());

    testRect.top += elapsedTime.asSeconds()* character.m_velocityY;
    result = collisions.collidedY(testRect, tilesMap);
    if(!result)
        character.characterRect.top += (character.m_velocityY * elapsedTime.asSeconds());
}
