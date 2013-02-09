// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Camera.h
// The header file of the Camera object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 06/12/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(int width, int height, float posX = 0, float posY = 0);

        // Functions to move the camera
            void moveX(sf::Rect<float> characterRect, sf::Vector2i worldSize);
            void moveY(sf::Rect<float> characterRect, sf::Vector2i worldSize);

        // Functions to get information about the camera
            sf::Vector2f getPosition() const;
            sf::Rect<float> getCameraRect () const;
            sf::Vector2i getOffset(sf::Vector2i tileSize) const;
            sf::Rect<int> getBounds(sf::Vector2i tileSize, sf::Vector2i worldSize) const;

    private:
        // Camera position and size
            sf::Rect<float> m_cameraRect;

        sf::Rect<float> m_targetRect;
};

#endif
