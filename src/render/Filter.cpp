// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Filter.cpp
// Filter is an alpha filter that we can apply gradually on the screen to
// change the color.
//
// Author: Sytten
// Creation date: 06/03/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#include "Filter.h"

Filter::Filter(sf::Color color, float alphaChange, sf::Rect<float> filterRect, bool toColor, float filterDelay) :
    m_filterDelay(filterDelay), m_alphaChange(alphaChange), m_color(color), m_active(true), m_toColor(toColor)
{
    m_filter.setPosition(filterRect.left, filterRect.top);
    m_filter.setSize(sf::Vector2f(filterRect.width, filterRect.height));
    setToColor(m_toColor);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::runFilter()
{
    if(m_active)
    {
        if(m_toColor)
        {
            if( (m_alpha < 255) && (m_filterClock.getElapsedTime().asSeconds() > m_filterDelay) )
            {
                m_color.a = (m_alpha += m_alphaChange);
                m_filter.setFillColor(m_color);
                m_filterClock.restart();
            }

            if(m_alpha >= 255)
            {
                m_color.a = 255;
                m_filter.setFillColor(m_color);
                m_active = false;
            }
        }

        else
        {
            if((m_alpha > 0) && (m_filterClock.getElapsedTime().asSeconds() > m_filterDelay))
            {
                m_color.a = (m_alpha -= m_alphaChange);
                m_filter.setFillColor(m_color);
                m_filterClock.restart();
            }

            if(m_alpha <= 0)
            {
                m_color.a = 0;
                m_filter.setFillColor(m_color);
                m_active = false;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::setToColor(bool toColor)
{
    m_toColor = toColor;

    if(m_toColor)
    {
        m_alpha = 0;
        m_color.a =  m_alpha;
        m_filter.setFillColor(m_color);
    }
    else
    {
        m_alpha = 255;
        m_color.a = m_alpha;
        m_filter.setFillColor(m_color);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::setColor(sf::Color color)
{
    m_color = color;
    setToColor(m_toColor);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Filter::setAlpha(float alpha)
{
    m_alpha = alpha;

    if(m_alpha < 0)
        m_alpha = 0;

    if(m_alpha > 255)
        m_alpha = 255;

    m_color.a = m_alpha;
    m_filter.setFillColor(m_color);
}
