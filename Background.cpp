#include "Background.h"
#include "ImageException.h"
#include <iostream>

using namespace std;

Background::Background(string backgroundFileName)
{
    if(!m_background.loadFromFile(backgroundFileName))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
}

Background::Background(std::string backgroundFileName, sf::Vector2f scale) : m_scale(scale)
{
    if(!m_background.loadFromFile(backgroundFileName))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
    m_backgroundSprite.setScale(m_scale);
}

void Background::setBackground(string backgroundFileName)
{
    if(!m_background.loadFromFile(backgroundFileName))
        throw ImageException(backgroundFileName);

    m_backgroundSprite.setTexture(m_background);
}

void Background::setBackgroundScale(sf::Vector2f scale)
{
    m_scale = scale;

    m_backgroundSprite.setScale(m_scale);
}
