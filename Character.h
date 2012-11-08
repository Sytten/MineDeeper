#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Character
{
    public:
    Character();

    private:
    sf::Texture characterTexture;
    float x, y;
    float speed;

    friend void draw(sf::RenderWindow &window, const Character *character);
};

#endif
