// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Character.cpp
// Character manages the variables of the player (position, speed,
// texture, etc.).
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Character.h"
#include "ImageException.h"

using namespace std;

Character::Character() : m_characterRect(375, 350, 75, 50), m_velocityX(0), m_velocityY(0), m_maxVelocity(300), m_digSpeed(2)
{
    // Load the character`s texture
        if(!m_characterTexture.loadFromFile("vehicule.png"))
            throw ImageException("vehicule.png"); // If it fails, throw an error

    m_characterSprite.setTexture(m_characterTexture);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::setCharacterTexture(string textureName)
{
    // Load the character`s texture
        if(!m_characterTexture.loadFromFile(textureName))
            throw ImageException(textureName); // If it fails, throw an error

    // Set the character's texture and adjust the view
        m_characterSprite.setTexture(m_characterTexture);
        m_characterSprite.setTextureRect(sf::Rect<int>(0,0,m_characterTexture.getSize().x,m_characterTexture.getSize().y));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::setCharacterPosition(float x, float y)
{
    m_characterSprite.setPosition(x, y);
}
