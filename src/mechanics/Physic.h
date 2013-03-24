// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Physic.h
// The header file of the Physic object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef PHYSIC_H
#define PHYSIC_H

class Physic
{
    public:
        Physic();

        // Functions relative to the gravity
            void addGravity(float& velocityY);
            void changeGravity(int gravity);

        // Function to check if the player must bounce
            bool checkRebound(float& velocitY);

    private:
        int m_gravity;

};

#endif // PHYSIC_H
