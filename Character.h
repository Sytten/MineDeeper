#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "CharacterMover.h"
#include "Collisions.h"

class Character
{
    public:
    Character();

    private:
    sf::Texture characterTexture;
    float x, y;
    float speed;

    friend void draw(sf::RenderWindow &window, const Character *character);
    friend void CharacterMover::move(Character *character);
    friend bool Collisions::collided(sf::RenderWindow const& window, Character *character, Map *map);
};

#endif
