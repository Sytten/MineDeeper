// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Bar.cpp
// Bar is an object who can display the life or the fuel of the character,
// for example.
//
// Author: Sytten
// Creation date: 03/02/2013
// Last modification date: 03/02/2013
// ---------------------------------------------------------------------------

#include <string>

#include "Bar.h"
#include "../exceptions/ImageException.h"

using namespace std;

Bar::Bar(string fullBarTextureName, string shapeBarTextureName, sf::Vector2f fullBarPos, sf::Vector2f shapeBarPos, Orientation orientation) : m_orientation(orientation)
{
    // Create the directory string
        string directory = "data/";

    // Load the textures
        directory += fullBarTextureName;
        if(!m_fullBarTexture.loadFromFile(directory))
            throw ImageException(fullBarTextureName);

        directory = "data/";
        directory += shapeBarTextureName;
        if(!m_shapeBarTexture.loadFromFile(directory))
            throw ImageException(shapeBarTextureName);

    // Set the textures and the positions
        m_fullBarSprite.setTexture(m_fullBarTexture);
        m_fullBarSprite.setPosition(fullBarPos);

        m_shapeBarSprite.setTexture(m_shapeBarTexture);
        m_shapeBarSprite.setPosition(shapeBarPos);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Bar::calculateBarSize(int const& maximum, int const& actual)
{
    if(m_orientation == HORIZONTAL) // Calculate the length of the bar, it's just the width who change
        m_fullBarSprite.setTextureRect(sf::Rect<int>(0, 0, (int)(actual*m_fullBarTexture.getSize().x/maximum), (int)m_fullBarTexture.getSize().y));

    if(m_orientation == VERTICAL) // Calculate the length of the bar, it's just the height who change
        m_fullBarSprite.setTextureRect(sf::Rect<int>(0, 0, m_fullBarTexture.getSize().x, (int)(actual*m_fullBarTexture.getSize().y/maximum)));
}
