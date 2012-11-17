#include "Character.h"

Character::Character() : m_velocityX(0), m_velocityY(0), m_maxVelocity(300)
{
    characterRect.top = 337.5;
    characterRect.left = 375;
    characterRect.width = 75;
    characterRect.height = 50;

    characterTexture.loadFromFile("vehicule.png"); //load the texture
}
