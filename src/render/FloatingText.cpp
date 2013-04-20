// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FloatingText.cpp
// FloatingText is text who change his position automatically during a period
// of time.
//
// Author: Sytten
// Creation date: 14/04/2013
// Last modification date: 15/04/2013
// ---------------------------------------------------------------------------

#include "FloatingText.h"
#include <iostream>

FloatingText::FloatingText(std::string text, std::string fontName, unsigned textSize, sf::Color textColor, sf::Vector2f position, sf::Vector2f targetPosition, sf::Time delay) :
    m_position(position), m_targetPosition(targetPosition), m_finished(false)
{
    if(!m_font.loadFromFile(fontName))
        std::cerr << "Couldn't load the font : " << fontName;

    else
        m_text.setFont(m_font);

    m_text.setString(text);
    m_text.setCharacterSize(textSize);
	m_text.setPosition(m_position);
	m_text.setColor(textColor);

	m_movement.x = (m_targetPosition.x - m_position.x) / (delay.asSeconds()*25);
	m_movement.y = (m_targetPosition.y - m_position.y) / (delay.asSeconds()*25);
}

FloatingText::FloatingText(std::string text, std::string fontName, unsigned textSize, sf::Color textColor, sf::Vector2f positionRelativeToObject, sf::Rect<float> objectCenteredOn,
                           FloatingText::Orientation axis, sf::Vector2f targetPositionRelativeToObject, bool stayCenteredOnObject, sf::Time delay) : m_finished(false)
{
    if(!m_font.loadFromFile(fontName))
        std::cerr << "Couldn't load the font : " << fontName;

    else
        m_text.setFont(m_font);

    m_text.setString(text);
    m_text.setCharacterSize(textSize);
	m_text.setPosition(m_position);
	m_text.setColor(textColor);

	if(axis == FloatingText::Orientation::X)
    {
        m_position.x = objectCenteredOn.left + (objectCenteredOn.width/2) - (m_text.getLocalBounds().width/2);
        m_position.y = positionRelativeToObject.y + objectCenteredOn.top;

        if(stayCenteredOnObject)
            m_targetPosition.x = m_position.x;
        else
            m_targetPosition.x = targetPositionRelativeToObject.x;

        m_targetPosition.y = targetPositionRelativeToObject.y + objectCenteredOn.top;
    }

    else if(axis == FloatingText::Orientation::Y)
    {
        m_position.y = objectCenteredOn.top + (objectCenteredOn.height/2) - (m_text.getLocalBounds().height/2);
        m_position.x = positionRelativeToObject.x + objectCenteredOn.left;

        if(stayCenteredOnObject)
            m_targetPosition.y = m_position.y;
        else
            m_targetPosition.y = targetPositionRelativeToObject.y + objectCenteredOn.top;

        m_targetPosition.x = targetPositionRelativeToObject.x + objectCenteredOn.left;
    }

	m_movement.x = (m_targetPosition.x - m_position.x) / (delay.asSeconds()*25);
	m_movement.y = (m_targetPosition.y - m_position.y) / (delay.asSeconds()*25);
}

void FloatingText::update()
{
	if(m_timer.getElapsedTime().asMilliseconds() >= 40 && !m_finished)
	{
	    // Movement in x axis
            if( ((m_position.x + m_movement.x) > m_targetPosition.x && m_position.x < m_targetPosition.x) || ((m_position.x + m_movement.x) < m_targetPosition.x && m_position.x > m_targetPosition.x) )
                m_position.x = m_targetPosition.x;

            else if(m_position.x != m_targetPosition.x)
                m_position.x += m_movement.x;

        //Movement in y axis
            if( ((m_position.y + m_movement.y) > m_targetPosition.y && m_position.y < m_targetPosition.y) || ((m_position.y + m_movement.y) < m_targetPosition.y && m_position.y > m_targetPosition.y) )
                m_position.y = m_targetPosition.y;

            else if(m_position.y != m_targetPosition.y)
                m_position.y += m_movement.y;

        // check the difference between target and position
            if((m_position.x - m_targetPosition.x <= 2.f && m_position.x - m_targetPosition.x > 0) || (m_targetPosition.x - m_position.x <= 2.f && m_targetPosition.x - m_position.x > 0))
                m_position.x = m_targetPosition.x;

            if((m_position.y - m_targetPosition.y <= 2.f && m_position.y - m_targetPosition.y > 0) || (m_targetPosition.y - m_position.y <= 2.f && m_targetPosition.y - m_position.y > 0))
                m_position.y = m_targetPosition.y;

        //If the it's finished
            if(m_position.x == m_targetPosition.x && m_position.y == m_targetPosition.y)
                m_finished = true;

		m_timer.restart();
	}
}

sf::Text const& FloatingText::getText(sf::Vector2f cameraPos)
{
    m_text.setPosition(m_position.x - cameraPos.x, m_position.y - cameraPos.y);
    return m_text;
}

