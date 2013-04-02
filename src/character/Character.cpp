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
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#include "Character.h"
#include "../exceptions/ImageException.h"

using namespace std;

Character::Character(int lastAirBlockY) : m_characterRect(381, 700, 63, 50), m_lastAirBlockY(lastAirBlockY), m_velocityX(0), m_velocityY(0), m_maxVelocity(300), m_digSpeed(2.5), m_digPower(0), m_protection(0)
{
    // Load the character`s texture
        if(!m_characterTexture.loadFromFile("data/vehicule.png"))
            throw ImageException("vehicule.png"); // If it fails, throw an error

    m_characterSprite.setTexture(m_characterTexture);

    m_altitudeFont.loadFromFile("data/ariblk.ttf");
    m_altitude.setColor(sf::Color::White);
    m_altitude.setFont(m_altitudeFont);
    m_altitude.setCharacterSize(20);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::setCharacterTexture(string textureName)
{
    // Load the character`s texture
        string directory = "data/";
            directory += textureName;
        if(!m_characterTexture.loadFromFile(directory))
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::setProperty( Property property, float newValue )
{
    if(property == Property::Engine)
        m_digSpeed = newValue;

    if(property == Property::Drill)
        m_digPower = newValue;

    if(property == Property::Storage)
        m_ressourcesInventory.m_maxResources = newValue;

    if(property ==  Property::Protection)
        m_protection = newValue;

    if(property == Property::Tank)
        m_fuel.m_maxFuel = newValue;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Character::getProperty( Property property )
{
    if(property == Property::Engine)
        return m_digSpeed;

    if(property == Property::Drill)
        return m_digPower;

    if(property == Property::Storage)
        return m_ressourcesInventory.m_maxResources;

    if(property == Property::Protection)
        return m_protection;

    if(property == Property::Tank)
        return m_fuel.m_maxFuel;

    return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Character::verifyAltitude(sf::Vector2i tileSize)
{
    m_altitudeString.clear();

    m_altitudeString += "Altitude : ";
    m_converter << (int)(((m_characterRect.top + m_characterRect.height)/tileSize.y - m_lastAirBlockY)*-5);
    m_altitudeString += m_converter.str();
    m_altitudeString += "ft";

    m_altitude.setString(m_altitudeString);
    m_altitude.setPosition(10, 130);

    m_converter.clear();
    m_converter.str(std::string());
}
