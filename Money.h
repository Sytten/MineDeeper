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

class Money
{
    public:
        Money();
        bool enoughMoney (unsigned const& cost) const;
        void addMoney(int const& moneyToAdd) { m_money += moneyToAdd; }
        void removeMoney(int const& moneyToRemove) { m_money -= moneyToRemove; }

    private:
        unsigned m_money;
};

#endif // MONEY_H
