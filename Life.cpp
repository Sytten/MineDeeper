// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Life.cpp
// Life manages the life of the character.
//
// Author: Sytten
// Creation date: 03/02/2013
// Last modification date: 03/02/2013
// ---------------------------------------------------------------------------

#include "Life.h"
#include <cstdlib>
#include <iostream>

               // Start with a full life
Life::Life() : m_life(100), m_maxLife(100), m_lifeBar("lifefull.png", "lifeshape.png", sf::Vector2f(19,13), sf::Vector2f(10,10))
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Life::isAlive() const
{
    // If the life is less than or equal to 0, return false cause the character is dead
        if(m_life <= 0)
            return false;

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Life::addLife(int const& lifeToAdd)
{
    // Add the life
        m_life += lifeToAdd;

    // If it's more than 100, set it to 100
        if(m_life > 100)
            m_life = 100;

    // Calculate the length of the bar
        m_lifeBar.calculateBarSize(m_maxLife, m_life);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Life::removeLife(int const& lifeToRemove)
{
    // Remove the life
        m_life -= lifeToRemove;

    // Is it's less than 0, set it to 0
        if(m_life < 0)
            m_life = 0;

    // Calculate the length of the bar
        m_lifeBar.calculateBarSize(m_maxLife, m_life);
}
