// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// KeyboardCharacterMover.cpp
// KeyboardCharacterMover handles the inputs from the keyboard and move
// the character. Also, the class provide a dig function.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "KeyboardCharacterMover.h"
#include "Character.h"
#include "TilesMap.h"
#include "Camera.h"
#include "Draw.h"
#include "ImageException.h"

// Set all the directions to false
KeyboardCharacterMover::KeyboardCharacterMover() : m_south(false), m_north(false), m_east(false), m_west(false), m_result(Collisions::NoCollision), m_flying(true)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardCharacterMover::addDirection(Direction direction)
{
    // Set the given direction to true, so we'll be able move our character in that direction
        switch(direction)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardCharacterMover::removeDirection(Direction direction) //set the given direction to false, so we don't move our character
{
// Set the given direction to false, so we won't move our character in that direction
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardCharacterMover::move(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Time elapsedTime)
{
// Check if we`re flying
    m_testRect = character.m_characterRect;
    m_testRect.top++;
    m_result = m_collisions.collidedY(m_testRect, tilesMap, m_blockPos);
    if(m_result == Collisions::NoCollision)
        m_flying = true;

// If a direction is true, add or delete 13 to the velocity (x or y) to be able to move in that direction
    if(m_north)
        character.m_velocityY -= 13.0f;

    if(m_south)
        character.m_velocityY += 3.0f; // Only add 3 if m_south is true (because we'll add the gravity

    if(m_east)
        character.m_velocityX += 13.0f;

    if(m_west)
        character.m_velocityX -= 13.0f;

// Add gravity (only if we're flying)
    if(m_flying)
        m_physic.addGravity(character.m_velocityY);

// If east or west are false et their velocity is not equal to 0
    if(!m_east && character.m_velocityX > 0)
    {
        character.m_velocityX = character.m_velocityX*95/100; // Reduce the velocity
            if(character.m_velocityX <= 5) // If the velocity is less than 5, set the velocity to 0
                character.m_velocityX = 0;
    }

    if(!m_west && character.m_velocityX < 0)
    {
        character.m_velocityX = character.m_velocityX*95/100; // Reduce the velocity
            if(character.m_velocityX >= -5) // If the velocity is more than -5, set the velocity to 0
                character.m_velocityX = 0;
    }

// Check if the velocity are higher than the max
    if(character.m_velocityX > character.m_maxVelocity)
        character.m_velocityX = character.m_maxVelocity;

    if(character.m_velocityX < -character.m_maxVelocity)
        character.m_velocityX = -character.m_maxVelocity;

    if(character.m_velocityY < -character.m_maxVelocity)
        character.m_velocityY = -character.m_maxVelocity;

    if(character.m_velocityY > 1000)
        character.m_velocityY = 1000;

// Check for collisions, if everything is ok: move the character. Else, check if we can dig
    m_testRect = character.m_characterRect;

    // Collisions in x axis
        m_testRect.left += elapsedTime.asSeconds()* character.m_velocityX; // Add x movement
        m_result = m_collisions.collidedX(m_testRect, tilesMap, m_blockPos); // Test

    // If there're no collision
        if(m_result == Collisions::NoCollision)
        {
            character.m_characterRect.left = m_testRect.left; // Move the character position
            camera.moveX(character.m_characterRect, tilesMap.getWorldSize()); // Move the camera position
        }
    // If we can dig
        else if(m_result == Collisions::Diggable)
        {
            // Only dig if we are not flying and if the the key is pressed
                if(m_blockPos.x < character.m_characterRect.left && m_west && !m_flying)
                {
                    dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::WEST);
                        character.m_velocityX = 0;
                    return;
                }
                if(m_blockPos.x > character.m_characterRect.left && m_east && !m_flying)
                {
                    dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::EAST);
                        character.m_velocityX = 0;
                    return;
                }
        }
        else
        {
            character.m_velocityX = 0;
        }

// Collisions in y axis
    m_testRect.left = character.m_characterRect.left; // Because we don't care about the movement in x axis
    m_testRect.top += elapsedTime.asSeconds()* character.m_velocityY; // Add y movement
    m_result = m_collisions.collidedY(m_testRect, tilesMap, m_blockPos); // Test
    // If there's no collision
        if(m_result == Collisions::NoCollision)
        {
            character.m_characterRect.top = m_testRect.top; // Move the character position
            camera.moveY(character.m_characterRect, tilesMap.getWorldSize()); // Move the camera position
        }
    // If we can dig
        else if(m_result == Collisions::Diggable)
        {
            // Only dig if the the key is pressed
                if(m_blockPos.y > character.m_characterRect.top && m_south && character.m_velocityY <= 700)
                {
                    m_flying = false;
                    dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::SOUTH);
                    character.m_velocityY = 0;
                }
            else
            {
                //Check rebound in y axis
                    m_physic.checkRebound(character.m_velocityY);

                //If there's no rebound
                    if(m_blockPos.y > character.m_characterRect.top && character.m_velocityY <= 700 && character.m_velocityY >= 0)
                    {
                        m_flying = false;
                        character.m_velocityY = 0;
                    }
            }
        }
        else
        {
            // Set the velocity to 0 if we hit
                character.m_velocityY = 0;
        }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardCharacterMover::dig(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Vector2i blockPos, Direction digDirection)
{
bool finished(false);

// Change character texture to dig
    if(digDirection == KeyboardCharacterMover::SOUTH)
        character.setCharacterTexture("digdown.png");

    if(digDirection == KeyboardCharacterMover::WEST)
        character.setCharacterTexture("digLeft.png");

    if(digDirection == KeyboardCharacterMover::EAST)
        character.setCharacterTexture("digRight.png");

// Find the target pos
    sf::Vector2i targetPos;
        targetPos.x = blockPos.x + (int)((tilesMap.getTileSize().x/2) - (character.m_characterRect.width/2));
        targetPos.y = blockPos.y + tilesMap.getTileSize().y - character.m_characterRect.height;

// Determine the movement in x and y that will be applied each 40ms
    sf::Vector2f movement;
    movement.x = (targetPos.x - character.m_characterRect.left)/(character.m_digSpeed*25);
    movement.y = (targetPos.y - character.m_characterRect.top)/(character.m_digSpeed*25);

// Start a clock
    sf::Clock clock;

while(!finished)
{
    // Check if the difference between the actual pos and the target pos is less than 1 px, if so just snap to the target
        if((targetPos.x - character.m_characterRect.left <= 1.0f && targetPos.x - character.m_characterRect.left >= 0) || (character.m_characterRect.left - targetPos.x <= 1.0f && character.m_characterRect.left - targetPos.x >= 0))
            character.m_characterRect.left = targetPos.x;

        if((targetPos.y - character.m_characterRect.top <= 1.0f && targetPos.y - character.m_characterRect.top >= 0) || (character.m_characterRect.top - targetPos.y <= 1.0f && character.m_characterRect.top - targetPos.y >= 0))
            character.m_characterRect.top = targetPos.y;

    // Move the character each 40ms
        if(clock.getElapsedTime().asMilliseconds() >= 40)
        {
            character.m_characterRect.left += movement.x;
            character.m_characterRect.top += movement.y;
            clock.restart();
        }

    // Move the camera
        camera.moveX(character.m_characterRect, tilesMap.getWorldSize());
        camera.moveY(character.m_characterRect, tilesMap.getWorldSize());

    // Display
        window.clear();
        draw(window, background);
        draw(window, tilesMap, camera);
            if(digDirection == KeyboardCharacterMover::WEST)
                character.m_characterRect.left -= 25;//remove a x px to the x of the because of the drill, we just want to remove those when draw but not when calculating
        draw(window, character, camera.getPosition());
            if(digDirection == KeyboardCharacterMover::WEST)
                character.m_characterRect.left += 25;//add a x px to the x of the because of the drill
        window.display();

    // Check if we reach the target
        if(targetPos.x == character.m_characterRect.left && targetPos.y == character.m_characterRect.top)
            finished = true;
}

// Change the block who has been dig to air
    tilesMap.setTile((blockPos.x/tilesMap.getTileSize().x), (blockPos.y/tilesMap.getTileSize().y), 2);

// Change character texture back to normal
    character.setCharacterTexture("vehicule.png");
}
