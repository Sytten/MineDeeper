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

    private:
    sf::Texture characterTexture;
    sf::Rect<float> characterRect;
    sf::Vector2<float> posInScreen;

    float m_velocityX;
    float m_velocityY;
    float m_maxVelocity;

    friend void draw(sf::RenderWindow &window, const Character &character, sf::Vector2f cameraPos);
    friend class KeyboardCharacterMover;
};

#endif
