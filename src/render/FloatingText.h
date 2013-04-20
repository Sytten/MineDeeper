// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FloatingText.h
// The header file of the FloatingText object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 14/04/2013
// Last modification date: 15/04/2013
// ---------------------------------------------------------------------------

#ifndef FLOATINGTEXT_H
#define FLOATINGTEXT_H

#include <string>

#include <SFML/Graphics.hpp>

class FloatingText
{
    public:
        enum Orientation{X, Y};

        FloatingText(std::string text, std::string fontName, unsigned textSize, sf::Color textColor, sf::Vector2f position, sf::Vector2f targetPosition, sf::Time delay);
        FloatingText(std::string text, std::string fontName, unsigned textSize, sf::Color textColor, sf::Vector2f positionRelativeToObject, sf::Rect<float> objectCenteredOn,
                     FloatingText::Orientation axis, sf::Vector2f targetPositionRelativeToObject, bool stayCenteredOnObject, sf::Time delay);

        void update();
        sf::Text const& getText(sf::Vector2f cameraPos);
        bool isFinished() const { return m_finished; }

    private:
        sf::Text m_text;
        sf::Font m_font;

        sf::Clock m_timer;
        sf::Vector2f m_position;
        sf::Vector2f m_targetPosition;
        sf::Vector2f m_movement;

        bool m_finished;
};

#endif // FLOATINGTEXT_H
