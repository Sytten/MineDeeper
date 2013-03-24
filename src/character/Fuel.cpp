// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Fuel.cpp
//Fuel manages the fuel of the character.
//
// Author: Sytten
// Creation date: 04/02/2013
// Last modification date: 04/02/2013
// ---------------------------------------------------------------------------

#include "Fuel.h"

Fuel::Fuel() : m_fuel(10), m_maxFuel(10), m_fuelBar("fuelfull.png", "fuelshape.png", sf::Vector2f(50,80), sf::Vector2f(10,70))
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Fuel::isEmpty() const
{
    // If the fuel is more than 0, return false because it's not empty
        if(m_fuel > 0)
            return false;

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Fuel::addFuel(int const& fuelToAdd)
{
    // Add the fuel
        m_fuel += fuelToAdd;

    // If it`s more than the max, set it to the max
        if(m_fuel > m_maxFuel)
            m_fuel = m_maxFuel;

    // Calculate the bar size
        m_fuelBar.calculateBarSize(m_maxFuel, m_fuel);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Fuel::removeFuel(int const& fuelToRemove)
{
    // Remove the fuel
        m_fuel -= fuelToRemove;

    // If it`s less than 0, set it to 0
        if(m_fuel < 0)
            m_fuel = 0;

    // Calculate the bar size
        m_fuelBar.calculateBarSize(m_maxFuel, m_fuel);
}
