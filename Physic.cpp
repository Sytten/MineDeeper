// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Physic.cpp
// Physic manages the gravity and the rebounds in the game
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Physic.h"

/////////////////////////////////////////////////////////////////////

Physic::Physic(): m_gravity(7)
{
}

/////////////////////////////////////////////////////////////////////

void Physic::addGravity(float& velocityY)
{
    velocityY += (float)m_gravity;
}

/////////////////////////////////////////////////////////////////////

void Physic::changeGravity(int gravity)
{
    m_gravity = gravity;
}

/////////////////////////////////////////////////////////////////////

bool Physic::checkRebound(float& velocityY)
{
    if(velocityY > 700)
    {
        velocityY /= -3;
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////
