#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>

class Character;
class TilesMap;

class Collisions
{
    public:
        bool collidedX(sf::Rect<float> const& characterRect, TilesMap &tilesMap);
        bool collidedY(sf::Rect<float> const& characterRect, TilesMap &tilesMap);
        bool collidedDecor(sf::Rect<float> const& characterRect, TilesMap &tilesMap);
};

#endif
