#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(int width, int height, float posX = 0, float posY = 0);

        void moveX(sf::Rect<float> characterRect, sf::Vector2i worldSize);
        void moveY(sf::Rect<float> characterRect, sf::Vector2i worldSize);
        sf::Vector2f getPosition() const;
        sf::Rect<float> getCameraRect () const;
        sf::Vector2i getOffset(sf::Vector2i tileSize) const;
        sf::Rect<int> getBounds(sf::Vector2i tileSize, sf::Vector2i worldSize) const;

    private:
        sf::Rect<float> m_cameraRect;
};

#endif
