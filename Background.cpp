// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Background.cpp
// Background manages the image of the background (texture, scale, etc.).
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Background.h"
#include "ImageException.h"
#include <iostream>

using namespace std;

Background::Background(string backgroundFileName)
{
    string directory = "data/";
        directory += backgroundFileName;

    if(!m_background.loadFromFile(directory))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
}

Background::Background(std::string backgroundFileName, sf::Vector2f scale) : m_scale(scale)
{
    string directory = "data/";
        directory += backgroundFileName;

    if(!m_background.loadFromFile(directory))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
    m_backgroundSprite.setScale(m_scale);
}

void Background::setBackground(string backgroundFileName)
{
    string directory = "data/";
        directory += backgroundFileName;

    if(!m_background.loadFromFile(directory))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
}

void Background::setBackgroundScale(sf::Vector2f scale)
{
    m_scale = scale;

    m_backgroundSprite.setScale(m_scale);
}
