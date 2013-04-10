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
#include "../render/Filter.h"

class TilesMap;

class Character
{
    public:
        Character(sf::Vector2f windowSize, int lastAirBlockY);

        // Setters of different variables
            void setCharacterTexture(std::string textureName);
            void setCharacterPosition(float x, float y);
            void setProperty( Property property, float newValue );
            void verifyAltitude(sf::Vector2i tileSize);
            void verifyOffset();

        // Getters of different variables
            Money& getMoney() { return m_money; }
            Artifacts& getArtifacts() { return m_artifacts; }
            Life& getLife() { return m_life; }
            Fuel& getFuel() { return m_fuel; }
            ResourcesInventory& getResourcesInventory() { return m_ressourcesInventory; }
            sf::Sprite const& getCharacterSprite() const { return m_characterSprite; }
            sf::Rect<float> const& getCharacterRect() const { return m_characterRect; }
            float getvelocity() const { return m_velocityY; }
            float getProperty( Property property ) const;
            sf::Text const& getAltitude() const { return m_altitude; }
            sf::Vector2f const& getOffset() const { return m_drawOffset; }
            Filter& getDamagesFilter() { return m_damagesFilter; }

    private:
        std::stringstream m_converter;

        sf::Texture m_characterTexture;
            sf::String m_characterTextureName;
        sf::Sprite m_characterSprite;
        sf::Rect<float> m_characterRect;
        sf::Vector2f m_drawOffset;
        sf::Text m_altitude;
            std::string m_altitudeString;
            sf::Font m_altitudeFont;
            int m_lastAirBlockY;

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

        // Filter when get damages
            Filter m_damagesFilter;

        // KeyboardCharacterMover now have full access to the private variables
            friend class KeyboardCharacterMover;
};

#endif
