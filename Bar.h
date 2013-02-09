// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Bar.h
// The header file of the Bar object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 03/02/2013
// Last modification date: 03/02/2013
// ---------------------------------------------------------------------------

#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class Bar
{
    public:
        enum Orientation{HORIZONTAL = 0, VERTICAL};

        Bar(std::string fullBarTextureName, std::string shapeBarTextureName, sf::Vector2f fullBarPos, sf::Vector2f shapeBarPos, Orientation orientation = HORIZONTAL);
        void calculateBarSize(int maximum, int actual);
        sf::Sprite const& getFullBarSprite() const { return m_fullBarSprite; }
        sf::Sprite const& getShapeBarSprite() const { return m_shapeBarSprite; }

    private:
        sf::Sprite m_fullBarSprite;
        sf::Texture m_fullBarTexture;

        sf::Texture m_shapeBarTexture;
        sf::Sprite m_shapeBarSprite;

        Orientation m_orientation;
};

#endif // BAR_H
