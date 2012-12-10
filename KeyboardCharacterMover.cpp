#include "KeyboardCharacterMover.h"
#include "Character.h"
#include "TilesMap.h"
#include "Camera.h"
#include <iostream>

KeyboardCharacterMover::KeyboardCharacterMover() : m_south(false), m_north(false), m_east(false), m_west(false), m_result(false) //set them all to false (security)
{
}

void KeyboardCharacterMover::addDirection(Direction direction)
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

void KeyboardCharacterMover::removeDirection(Direction direction) //set the given direction to false, so we don't move our character
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

void KeyboardCharacterMover::move(Character &character, TilesMap &tilesMap, Camera &camera, sf::Time elapsedTime)
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
    m_testRect = character.characterRect;

    m_testRect.left += elapsedTime.asSeconds()* character.m_velocityX; //add movement to x
    m_result = m_collisions.collidedX(m_testRect, tilesMap); //check if collided
    if(!m_result) //if not, move the posisiton of the character and the position of the camera
    {
        character.characterRect.left = m_testRect.left;
        camera.moveX(character.characterRect, tilesMap.getWorldSize());
    }

    //std::cout << "movement X succes" << std::endl;

    m_testRect.top += elapsedTime.asSeconds()* character.m_velocityY; //add movement to y
    m_result = m_collisions.collidedY(m_testRect, tilesMap); //check if collided
    if(!m_result) //if not, move the posisiton of the character and the position of the camera
    {
        character.characterRect.top = m_testRect.top;
        //std::cout << "character.top: " << character.characterRect.top << std::endl;
        camera.moveY(character.characterRect, tilesMap.getWorldSize());
    }

    //std::cout << "movement y succes" << std::endl;
}
