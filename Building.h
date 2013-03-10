// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Building.h
// Generic class for the different buildings in the game
//
// Author: Sytten
// Creation date: 05/03/2013
// Last modification date: 05/03/2013
// ---------------------------------------------------------------------------

#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

class Character;

class Building
{
    public:
        Building(unsigned const& ID) : m_ID(ID) {}
        virtual bool enter(sfg::SFGUI &sfgui, sf::RenderWindow &window, Character *ptrCharacter) = 0;
        virtual unsigned const& getID() const { return m_ID; }
    protected:
        unsigned m_ID;
};

#endif // BUILDING_H
