#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(int width, int height, float posX = 0, float posY = 0);

        void moveX(sf::Rect<float> characterRect, sf::Vector2<int> worldSize);
        void moveY(sf::Rect<float> characterRect, sf::Vector2<int> worldSize);
        sf::Vector2<float> getPosition() const;
        sf::Vector2<int> getOffset(sf::Vector2<int> tileSize) const;
        sf::Rect<int> getBounds(sf::Vector2<int> tileSize) const;

    private:
        sf::Rect<float> m_cameraRect;
};

#endif
