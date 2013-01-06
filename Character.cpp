#include "Character.h"
#include "ImageException.h"

using namespace std;

Character::Character() : characterRect(375, 350, 75, 50), m_velocityX(0), m_velocityY(0), m_maxVelocity(300), m_digSpeed(2)
{
    if(!m_characterTexture.loadFromFile("vehicule.png"))//load the texture
        throw ImageException("vehicule.png");

    m_characterSprite.setTexture(m_characterTexture);
}

void Character::setCharacterTexture(string textureName)
{
    if(!m_characterTexture.loadFromFile(textureName))
        throw ImageException(textureName);

    m_characterSprite.setTexture(m_characterTexture);
    m_characterSprite.setTextureRect(sf::Rect<int>(0,0,m_characterTexture.getSize().x,m_characterTexture.getSize().y));
}

void Character::setCharacterPosition(float x, float y)
{
    m_characterSprite.setPosition(x, y);
}
