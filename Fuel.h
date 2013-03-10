// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Fuel.h
// The header file of the Fuel object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 04/02/2013
// Last modification date: 04/02/2013
// ---------------------------------------------------------------------------

#ifndef FUEL_H
#define FUEL_H

#include <SFML/Graphics.hpp>

#include "Bar.h"
#include "FuelBuilding.h"

class Fuel
{
    public:
        Fuel();
        bool isEmpty() const;
        void addFuel(int const& fuelToAdd);
        void removeFuel(int const& fuelToRemove);
        int fuelNeededToBeFull() const { return m_maxFuel - m_fuel; }
        sf::Sprite const& getFullFuelBarSprite() const { return m_fuelBar.getFullBarSprite(); }
        sf::Sprite const& getShapeFuelBarSprite() const { return m_fuelBar.getShapeBarSprite(); }

    private:
        int m_fuel;
        int m_maxFuel;
        Bar m_fuelBar;

    friend class FuelBuilding;
};

#endif // FUEL_H
