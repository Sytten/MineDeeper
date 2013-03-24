// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Life.h
// The header file of the Life object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 03/02/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#ifndef LIFE_H
#define LIFE_H

#include "../gui/Bar.h"

class Life
{
    public:
        Life();
        bool isAlive() const;
        void addLife(int const& lifeToAdd);
        void removeLife(int const& lifeToRemove);
        int lifeNeededToBeFull() const { return m_maxLife - m_life; } // For the full function
        float fractionOfLifeFull() { return (float)m_life / (float)m_maxLife; }
        sf::Sprite const& getFullLifeBarSprite() const { return m_lifeBar.getFullBarSprite(); }
        sf::Sprite const& getShapeLifeBarSprite() const { return m_lifeBar.getShapeBarSprite(); }

    private:
        int m_life;
        const int m_maxLife;
        Bar m_lifeBar;
};

#endif // LIFE_H
