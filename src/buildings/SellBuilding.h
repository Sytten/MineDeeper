// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// SellBuilding.h
// The header file of the SellBuilding object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 23/02/2013
// Last modification date: 09/03/2013
// ---------------------------------------------------------------------------

#ifndef SELLBUILDING_H
#define SELLBUILDING_H

#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Building.h"
#include "../ServiceLocator.h"

class Character;

class SellBuilding : public Building
{
    public:
        SellBuilding(sf::Vector2f const& windowSize, unsigned const& ID);
        virtual bool enter(sfg::SFGUI &sfgui, sf::RenderWindow &window, Character *ptrCharacter);

        // Function to set the money label
            void setMoneyLabel();

    private:
        void sellButtonClick();
        void exitButtonClick() { m_wantToExit = true; }

        bool m_wantToExit;
        unsigned m_totalToSell;
        Character *m_ptrCharacter;

        sfg::Window::Ptr m_window;

        sfg::Label::Ptr m_titleLabel;
        sfg::Label::Ptr m_moneyLabel;
            sf::String m_money;
            std::ostringstream m_converter;
        sfg::Frame::Ptr m_mainFrame;
        sfg::Box::Ptr m_mainVerticalLayout;
        sfg::Button::Ptr m_sellButton;
            sfg::Box::Ptr m_horizontalAlignmentLayout;
            sfg::Alignment::Ptr m_sellButtonAlignment;
        sfg::Button::Ptr m_exitButton;
};

#endif // SELLBUILDING_H
