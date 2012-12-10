#include "Character.h"

Character::Character() : characterRect(375, 350, 75, 50), m_velocityX(0), m_velocityY(0), m_maxVelocity(300)
{
    characterTexture.loadFromFile("vehicule.png"); //load the texture
}
