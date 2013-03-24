// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Money.h
// The header file of the Character object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 28/01/2013
// Last modification date: 31/01/2013
// ---------------------------------------------------------------------------

#ifndef MONEY_H
#define MONEY_H

#include "../buildings/FuelBuilding.h"
#include "../buildings/SellBuilding.h"
#include "../buildings/UpgradeBuilding.h"

class Money
{
    public:
        Money();
        bool enoughMoney (unsigned const& cost) const;
        void addMoney(unsigned const& moneyToAdd) { m_money += moneyToAdd; }
        void removeMoney(unsigned const& moneyToRemove) { m_money -= moneyToRemove; }

    private:
        unsigned m_money;

    friend void FuelBuilding::setMoneyLabel();
    friend void SellBuilding::setMoneyLabel();
    friend void UpgradeBuilding::setMoneyLabel();
};

#endif // MONEY_H
