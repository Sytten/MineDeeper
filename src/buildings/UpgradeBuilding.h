// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// UpgradeBuilding.h
// The header file of the UpgradeBuilding object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 23/03/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#ifndef UPGRADEBUILDING_H
#define UPGRADEBUILDING_H

#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Building.h"
#include "../exceptions/ImageException.h"
#include "../character/Property.h"

class Character;

class UpgradeBuilding : public Building
{
    public:
        UpgradeBuilding(sf::Vector2f const& windowSize, unsigned const& ID);
        virtual bool enter(sfg::SFGUI& sfgui, sf::RenderWindow& window, Character *ptrCharacter);

        // Function to set the money label
            void setMoneyLabel();

    private:
        int to_int(std::string stringToConvert);
        void verifyButtonsState();

        // Generic function for the 5, 10, 25 and 50$ buttons
            void moneyButtonClick( int life );

        // Slots
            void button5Click() { moneyButtonClick(5 / m_lifePrice); }
            void button10Click() { moneyButtonClick(10 / m_lifePrice); }
            void button25Click() { moneyButtonClick(25 / m_lifePrice); }
            void button50Click() { moneyButtonClick(50 / m_lifePrice); }
            void fullButtonClick();
            void exitButtonClick() { m_wantToExit = true; }
            void upgradeButtonClick();

        struct Upgrade
        {
            public:
            Property upgradeType;
            unsigned level;
            unsigned price;
        };

        const float m_lifePrice;
        bool m_wantToExit;
        Character *m_ptrCharacter;

        sfg::Window::Ptr m_window;

        sfg::Box::Ptr m_mainVerticalLayout;
        sfg::Label::Ptr m_titleLabel;
        sfg::Label::Ptr m_moneyLabel;
            sf::String m_moneyString;
            std::stringstream m_converter;
        sfg::Notebook::Ptr m_notebook;
            std::map<sfg::Button::Ptr, Upgrade> m_upgrades;
        sfg::Separator::Ptr m_separator;
        sfg::ProgressBar::Ptr m_lifeBar;
        sfg::Box::Ptr m_verticalButtonsLayout1;
            sfg::Button::Ptr m_5Button;
            sfg::Button::Ptr m_10Button;
        sfg::Box::Ptr m_verticalButtonsLayout2;
            sfg::Button::Ptr m_25Button;
            sfg::Button::Ptr m_50Button;
        sfg::Box::Ptr m_horizontalButtonsLayout;
            sfg::Button::Ptr m_fullButton;
        sfg::Button::Ptr m_exitButton;
};

#endif // UPGRADEBUILDING_H
