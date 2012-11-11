#include "Character.h"

Character::Character()
{
    characterTexture.loadFromFile("vehicule.png"); //load the texture
    speed = 1.f; //set speed
    x =  375; //set initial position
    y =  337.5;
}


