#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "KeyboardCharacterMover.h"
#include "Collisions.h"

class TilesMap;

class Character
{
    public:
        Character();

        void setCharacterTexture(std::string textureName);
        void setCharacterPosition(float x, float y);

        sf::Sprite const& getCharacterSprite() const { return m_characterSprite; }
        sf::Rect<float> const& getCharacterRect() const { return characterRect; }

    private:
        sf::Texture m_characterTexture;
        sf::Sprite m_characterSprite;
        sf::Rect<float> characterRect;

        float m_velocityX;
        float m_velocityY;
        float m_maxVelocity;
        float m_digSpeed; //in seconds

        friend class KeyboardCharacterMover;
};

#endif
