// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Camera.cpp
// Camera manages the part of the map that the player can see.
//
// Author: Sytten
// Creation date: 06/12/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera(int width, int height, float posX, float posY) : m_cameraRect(posX, posY, width, height)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveX(sf::Rect<float> characterRect, sf::Vector2i worldSize)
{
// Add the x movement
    m_targetRect = m_cameraRect;
        m_targetRect.left = characterRect.left + (characterRect.width/2) - (m_targetRect.width/2);

// Test if we can move
    if(!(m_targetRect.left < 0 || m_targetRect.left + m_targetRect.width > worldSize.x))
        m_cameraRect = m_targetRect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveY(sf::Rect<float> characterRect, sf::Vector2i worldSize)
{
// Add the y movement
    m_targetRect = m_cameraRect;
        m_targetRect.top = characterRect.top + (characterRect.height/2) - (m_targetRect.height/2);

// Test if we can move
    if(!(m_targetRect.top < 0 || m_targetRect.top + m_targetRect.height > worldSize.y))
        m_cameraRect = m_targetRect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2f Camera::getPosition() const
{
// Return the camera position
    return sf::Vector2f(m_cameraRect.left, m_cameraRect.top);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Camera::getOffset(sf::Vector2i tileSize) const
{
// Calculate and return the camera offset
    return sf::Vector2i((int)(m_cameraRect.left) % (tileSize.x), (int)(m_cameraRect.top) % (tileSize.y));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Rect<int> Camera::getBounds(sf::Vector2i tileSize, sf::Vector2i worldSize) const
{
// If we touch the limit of the screen we don't need one more tile in x
    if(m_cameraRect.left + m_cameraRect.width == worldSize.x)
        return sf::Rect<int>((int)(m_cameraRect.left / tileSize.x), (int)(m_cameraRect.top / tileSize.y), (int)(m_cameraRect.width / tileSize.x), (int)(m_cameraRect.height / tileSize.y + 1));

// Else return with one tile more in x and y
    return sf::Rect<int>((int)(m_cameraRect.left / tileSize.x), (int)(m_cameraRect.top / tileSize.y), (int)(m_cameraRect.width / tileSize.x + 1), (int)(m_cameraRect.height / tileSize.y + 1));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Rect<float> Camera::getCameraRect () const
{
// Return the camera rectangle
    return m_cameraRect;
}
