// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Money.cpp
// Money manages the money of the player.
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 31/01/2013
// ---------------------------------------------------------------------------

#include "Money.h"

Money::Money() : m_money(500)
{
}

bool Money::enoughMoney (unsigned const& cost) const
{
// If the cost is higher than the player's money, return false.
    if(cost > m_money)
        return false;

    return true;
}
