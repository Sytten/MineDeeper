// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Character.h
// The header file of the Money object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

#include "KeyboardCharacterMover.h"
#include "Artifacts.h"
#include "Money.h"
#include "Life.h"
#include "ResourcesInventory.h"
#include "Fuel.h"
#include "Property.h"

class TilesMap;

class Character
{
    public:
        Character();

        // Setters of different variables
            void setCharacterTexture(std::string textureName);
            void setCharacterPosition(float x, float y);
            void setProperty( Property property, float newValue );

        // Getters of different variables
            Money& getMoney() { return m_money; }
            Artifacts& getArtifacts() { return m_artifacts; }
            Life& getLife() { return m_life; }
            Fuel& getFuel() { return m_fuel; }
            ResourcesInventory& getResourcesInventory() { return m_ressourcesInventory; }
            sf::Sprite const& getCharacterSprite() const { return m_characterSprite; }
            sf::Rect<float> const& getCharacterRect() const { return m_characterRect; }
            float getvelocity() { return m_velocityY; }
            float getProperty( Property property );

    private:
        sf::Texture m_characterTexture;
        sf::Sprite m_characterSprite;
        sf::Rect<float> m_characterRect;

        float m_velocityX;
        float m_velocityY;
        float m_maxVelocity;

        float m_digSpeed; // In seconds
        float m_digPower;
        float m_protection;

        Life m_life;
        Fuel m_fuel;
        Artifacts m_artifacts;
        Money m_money;
        ResourcesInventory m_ressourcesInventory;

        // KeyboardCharacterMover now have full access to the private variables
            friend class KeyboardCharacterMover;
};

#endif
