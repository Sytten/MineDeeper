#include "Camera.h"
#include <iostream>

using namespace std;

Camera::Camera(int width, int height, float posX, float posY) : m_cameraRect(posX, posY, width, height)
{
}

void Camera::moveX(sf::Rect<float> characterRect, sf::Vector2<int> worldSize)
{
    sf::Rect<float> m_targetRect = m_cameraRect;

    //std::cout << "m_cameraRect.left: " << m_cameraRect.left << std::endl;

    m_targetRect.left = characterRect.left + (characterRect.width/2) - (m_targetRect.width/2);

    //std::cout << "characterRect.left: " << characterRect.left << std::endl;

    if(!(m_targetRect.left < 0 || m_targetRect.left + m_targetRect.width > worldSize.x))
        m_cameraRect = m_targetRect;

    //std::cout << "m_cameraRect.left: " << m_cameraRect.left << std::endl;

    cout << "camera.width: " << m_cameraRect.width << endl;
    cout << "camera.height: " << m_cameraRect.height << endl;
    cout << "characterRect.top: " << characterRect.top << endl;
    cout << "characterRect.left: " << characterRect.left << endl;
    cout << "characterRect.width: " << characterRect.width << endl;
    cout << "characterRect.height: " << characterRect.height << endl;
    cout << "worldsize.x" << worldSize.x << endl;
    cout << "worldsize.y" << worldSize.y << endl;
}

void Camera::moveY(sf::Rect<float> characterRect, sf::Vector2<int> worldSize)
{
    sf::Rect<float> m_targetRect = m_cameraRect;

    //std::cout << "m_cameraRect.top: " << m_cameraRect.top << std::endl;

    m_targetRect.top = characterRect.top + (characterRect.height/2) - (m_targetRect.height/2);

    //std::cout << "m_targetRect.top: " << m_targetRect.top << std::endl;

    //std::cout << "worldsize.y: " << worldSize.y << std::endl;

    if(!(m_targetRect.top < 0 || m_targetRect.top + m_targetRect.height > worldSize.y))
        m_cameraRect = m_targetRect;

    //std::cout << "m_cameraRect.top: " << m_cameraRect.top << std::endl;
}

sf::Vector2<float> Camera::getPosition() const
{
    sf::Vector2<float> cameraPos;

    cameraPos.x = m_cameraRect.left;
    cameraPos.y = m_cameraRect.top;

    return cameraPos;
}

sf::Vector2<int> Camera::getOffset(sf::Vector2<int> tileSize) const
{
    sf::Vector2<int> cameraOffset;

    cameraOffset.x = (int)(m_cameraRect.left) % (tileSize.x);
    cameraOffset.y = (int)(m_cameraRect.top) % (tileSize.y);

    //std::cout << "cameraOffset.y: " << cameraOffset.y << std::endl;
    //std::cout << "cameraOffset.x: " << cameraOffset.x << std::endl;

    return cameraOffset;
}

sf::Rect<int> Camera::getBounds(sf::Vector2<int> tileSize) const
{
    int x = (int)(m_cameraRect.left / tileSize.x);
    int y = (int)(m_cameraRect.top / tileSize.y);

    //std::cout << "bound x: " << x << std::endl;
    //std::cout << "bound y: " << y << std::endl;

    //+1 in case camera size isn't divisible by tileSize
    int w = (int)(m_cameraRect.width / tileSize.x + 1);
    int h = (int)(m_cameraRect.height / tileSize.y + 1);

    //std::cout << "bound w: " << w << std::endl;
    //std::cout << "bound h: " << h << std::endl;

    //And +1 again if we're offset from the tile
    /*if(x % (tileSize.x) != 0)
        w++;
    if(y % (tileSize.y) != 0)
       h++;*/

    //std::cout << "bound w: " << w << std::endl;
    //std::cout << "bound h: " << h << std::endl;

    return sf::Rect<int>(x,y,w,h);
}
