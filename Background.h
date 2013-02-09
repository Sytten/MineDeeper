// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Background.h
// The header file of the Background object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background
{
    public:
        Background(std::string backgroundFileName);
        Background(std::string backgroundFileName, sf::Vector2f scale);

        sf::Texture const& getBackground() const { return m_background; }
        void setBackground(std::string backgroundFileName);

        sf::Vector2f const& getBackgroundScale() const { return m_scale; }
        void setBackgroundScale(sf::Vector2f scale);

        sf::Sprite const& getBackgroundSprite() const { return m_backgroundSprite; }

    private:
        sf::Texture m_background;
        sf::Vector2f m_scale;
        sf::Sprite m_backgroundSprite;
};

#endif // BACKGROUND_H
