#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>

class Character;
class TilesMap;

class Collisions
{
    public:
        enum CollisionType{NoCollision, Collision, Diggable};

        CollisionType collidedX(sf::Rect<float> const& characterRect, TilesMap const& tilesMap, sf::Vector2i &blockPos);
        CollisionType collidedY(sf::Rect<float> const& characterRect, TilesMap const& tilesMap, sf::Vector2i &blockPos);

    private:
        int m_xmin;
        int m_xmax;
        int m_ymin;
        int m_ymax;
};

#endif
