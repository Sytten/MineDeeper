// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// FuelBuilding.h
// The header file of the FuelBuilding object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 21/02/2013
// Last modification date: 23/03/2013
// ---------------------------------------------------------------------------

#ifndef FUELBUILDING_H
#define FUELBUILDING_H

#include <stdexcept>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Building.h"

class Character;

class FuelBuilding : public Building
{
    public:
        FuelBuilding(sf::Vector2f const& windowSize, unsigned const& ID);
        virtual bool enter(sfg::SFGUI& sfgui, sf::RenderWindow& window, Character *ptrCharacter);

        // Function to set the money label
            void setMoneyLabel();

    private:
        // Generic function for the 5, 10, 25 and 50$ buttons
            void moneyButtonClick( int liters);

        // Slots
            void button5Click() { moneyButtonClick(5 / m_fuelPrice); }
            void button10Click() { moneyButtonClick(10 / m_fuelPrice); }
            void button25Click() { moneyButtonClick(25 / m_fuelPrice); }
            void button50Click() { moneyButtonClick(50 / m_fuelPrice); }
            void fullButtonClick();
            void exitButton() { m_wantToExit = true; }

        // Some variables
            const float m_fuelPrice;
            bool m_wantToExit;
            Character *m_ptrCharacter;

        // Main sfgui window
            sfg::Window::Ptr m_window;

        // Images
            sfg::Image::Ptr m_fuelPump;
                sf::Image m_fuelPumpImage;
            /*sfg::Image::Ptr m_shapeTank;
                sf::Image m_shapeTankImage;
            sfg::Image::Ptr m_fullTank;
                sf::Image m_fullTankImage;*/
            sfg::ProgressBar::Ptr m_tank; // Temporary

        // Labels
            sfg::Label::Ptr m_moneyLabel;
                sf::String m_money;
                std::ostringstream m_converter;
            sfg::Label::Ptr m_titleLabel;

        // Buttons
            sfg::Button::Ptr m_5Button;
            sfg::Button::Ptr m_10Button;
            sfg::Button::Ptr m_25Button;
            sfg::Button::Ptr m_50Button;
            sfg::Button::Ptr m_fullButton;
            sfg::Button::Ptr m_exitButton;
                sf::Image m_exitButtonImage;

        // Layouts
            sfg::Box::Ptr m_mainVerticalLayout;
            sfg::Box::Ptr m_mainHorizontalLayout;
            sfg::Box::Ptr m_buttonHorizontalLayout1;
            sfg::Box::Ptr m_buttonHorizontalLayout2;
            sfg::Box::Ptr m_buttonVerticalLayout;
            //sfg::Table::Ptr m_mainTable; //Implement later if we have time
};

#endif // FUELBUILDING_H
