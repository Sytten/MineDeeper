#include "KeyboardCharacterMover.h"
#include "Character.h"
#include "TilesMap.h"
#include "Camera.h"
#include "Draw.h"
#include "ImageException.h"

KeyboardCharacterMover::KeyboardCharacterMover() : m_south(false), m_north(false), m_east(false), m_west(false), m_result(Collisions::NoCollision) //set them all to false (security)
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


void KeyboardCharacterMover::move(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Time elapsedTime)
{
    //if the 2 directions are set to false, then set the velocity to 0
    if(!m_north && !m_south)
        character.m_velocityY = 0;

    if(!m_east && !m_west)
        character.m_velocityX = 0;


    //if one direction is true, add ou delete 3 to the velocity (x or y)
    if(m_north)
        character.m_velocityY -= 13.0f;

    if(m_south)
        character.m_velocityY += 13.0f;

    if(m_east)
        character.m_velocityX += 13.0f;

    if(m_west)
        character.m_velocityX -= 13.0f;


    //check if the velocity are higher than the max
    if(character.m_velocityX > character.m_maxVelocity)
        character.m_velocityX = character.m_maxVelocity;

    if(character.m_velocityX < -character.m_maxVelocity)
        character.m_velocityX = -character.m_maxVelocity;

    if(character.m_velocityY > character.m_maxVelocity)
        character.m_velocityY = character.m_maxVelocity;

    if(character.m_velocityY < -character.m_maxVelocity)
        character.m_velocityY = -character.m_maxVelocity;


    //check for collisions, if everything is ok: move the character, else dig
    m_testRect = character.characterRect;


    //collisions in x axis
    m_testRect.left += elapsedTime.asSeconds()* character.m_velocityX; //add movement
    m_result = m_collisions.collidedX(m_testRect, tilesMap, m_blockPos);
    if(m_result == Collisions::NoCollision) //if there're no collisions, move the positions of the character and the camera
    {
        character.characterRect.left = m_testRect.left;
        camera.moveX(character.characterRect, tilesMap.getWorldSize());
    }
    else if(m_result == Collisions::Diggable)
    {
        if(m_blockPos.x < character.characterRect.left && m_west)
        {
            dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::WEST);
            character.m_velocityX = 0;
            return;
        }
        if(m_blockPos.x > character.characterRect.left && m_east)
        {
            dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::EAST);
            character.m_velocityX = 0;
            return;
        }
    }
    else
    {
        m_testRect.left = character.characterRect.left;
    }

    //collisions in y axis
    m_testRect.top += elapsedTime.asSeconds()* character.m_velocityY; //add movement
    m_result = m_collisions.collidedY(m_testRect, tilesMap, m_blockPos);
    if(m_result == Collisions::NoCollision) //if there're no collisions, move the positions of the character and the camera
    {
        character.characterRect.top = m_testRect.top;
        camera.moveY(character.characterRect, tilesMap.getWorldSize());
    }
    else if(m_result == Collisions::Diggable)
    {
        if(m_blockPos.y > character.characterRect.left && m_south)
        {
            dig(window, character, tilesMap, camera, background, m_blockPos, KeyboardCharacterMover::SOUTH);
            character.m_velocityY = 0;
        }
    }
}


void KeyboardCharacterMover::dig(sf::RenderWindow &window, Character &character, TilesMap &tilesMap, Camera &camera, Background &background, sf::Vector2i blockPos, Direction digDirection)
{
    bool finished(false);

    //change character texture to dig
    if(digDirection == KeyboardCharacterMover::SOUTH)
        character.setCharacterTexture("digdown.png");

    if(digDirection == KeyboardCharacterMover::WEST)
        character.setCharacterTexture("digLeft.png");

    if(digDirection == KeyboardCharacterMover::EAST)
        character.setCharacterTexture("digRight.png");

    //Find the target pos
    sf::Vector2i targetPos;
        targetPos.x = blockPos.x + (int)((tilesMap.getTileSize().x/2) - (character.characterRect.width/2));
        targetPos.y = blockPos.y + tilesMap.getTileSize().y - character.characterRect.height;

    //Determine the movement in x and y that will be applied each 40ms
    sf::Vector2f movement;
    movement.x = (targetPos.x - character.characterRect.left)/(character.m_digSpeed*25);
    movement.y = (targetPos.y - character.characterRect.top)/(character.m_digSpeed*25);

    //start a clock
    sf::Clock clock;

    while(!finished)
    {
        //check if the difference between the actual pos and the target pos is less than 1 px, if so just snap to the target
        if((targetPos.x - character.characterRect.left <= 1.0f && targetPos.x - character.characterRect.left >= 0) || (character.characterRect.left - targetPos.x <= 1.0f && character.characterRect.left - targetPos.x >= 0))
            character.characterRect.left = targetPos.x;

        if((targetPos.y - character.characterRect.top <= 1.0f && targetPos.y - character.characterRect.top >= 0) || (character.characterRect.top - targetPos.y <= 1.0f && character.characterRect.top - targetPos.y >= 0))
            character.characterRect.top = targetPos.y;

        //move the character each 40ms
        if(clock.getElapsedTime().asMilliseconds() >= 40)
        {
            character.characterRect.left += movement.x;
            character.characterRect.top += movement.y;
            clock.restart();
        }

        //move the camera
        camera.moveX(character.characterRect, tilesMap.getWorldSize());
        camera.moveY(character.characterRect, tilesMap.getWorldSize());

        //display
        window.clear();
        draw(window, background);
        draw(window, tilesMap, camera);
            if(digDirection == KeyboardCharacterMover::WEST)
                character.characterRect.left -= 25;//remove a x px to the x of the because of the drill, we just want to remove those when draw but not when calculating
        draw(window, character, camera.getPosition());
            if(digDirection == KeyboardCharacterMover::WEST)
                character.characterRect.left += 25;//add a x px to the x of the because of the drill
        window.display();

        //check if we reach the target, if so finished the dig loop
        if(targetPos.x == character.characterRect.left && targetPos.y == character.characterRect.top)
            finished = true;
    }

    //change the block who has been dig to air
    tilesMap.setTile((blockPos.x/tilesMap.getTileSize().x), (blockPos.y/tilesMap.getTileSize().y), 0);

    //change character texture back to normal
    character.setCharacterTexture("vehicule.png");
}
