#include "Camera.h"

Camera::Camera(int width, int height, float posX, float posY) : m_cameraRect(posX, posY, width, height)
{
}

void Camera::moveX(sf::Rect<float> characterRect, sf::Vector2i worldSize)
{
    sf::Rect<float> m_targetRect = m_cameraRect;
        m_targetRect.left = characterRect.left + (characterRect.width/2) - (m_targetRect.width/2);

    if(!(m_targetRect.left < 0 || m_targetRect.left + m_targetRect.width > worldSize.x))
        m_cameraRect = m_targetRect;
}

void Camera::moveY(sf::Rect<float> characterRect, sf::Vector2i worldSize)
{
    sf::Rect<float> m_targetRect = m_cameraRect;
        m_targetRect.top = characterRect.top + (characterRect.height/2) - (m_targetRect.height/2);

    if(!(m_targetRect.top < 0 || m_targetRect.top + m_targetRect.height > worldSize.y))
        m_cameraRect = m_targetRect;
}

sf::Vector2f Camera::getPosition() const
{
    return sf::Vector2f(m_cameraRect.left, m_cameraRect.top);
}

sf::Vector2i Camera::getOffset(sf::Vector2i tileSize) const
{
    return sf::Vector2i((int)(m_cameraRect.left) % (tileSize.x), (int)(m_cameraRect.top) % (tileSize.y));
}

sf::Rect<int> Camera::getBounds(sf::Vector2i tileSize) const
{
    return sf::Rect<int>((int)(m_cameraRect.left / tileSize.x), (int)(m_cameraRect.top / tileSize.y), (int)(m_cameraRect.width / tileSize.x + 1), (int)(m_cameraRect.height / tileSize.y + 1));
}

sf::Rect<float> Camera::getCameraRect () const
{
    return m_cameraRect;
}
