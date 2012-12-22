#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>

class Character;
class TilesMap;

class Collisions
{
    public:
        bool collidedX(sf::Rect<float> const& characterRect, TilesMap const& tilesMap);
        bool collidedY(sf::Rect<float> const& characterRect, TilesMap const& tilesMap);
        bool collidedDecor(sf::Rect<float> const& characterRect, TilesMap const& tilesMap);
};

#endif
