// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// MainMenu.h
// The header file of the MainMenu object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef MAINMENU_H
#define MAINMENU_H

#include <List>

#include <SFML/Graphics.hpp>

class MainMenu
{
    public:
        MainMenu();

        enum MenuChoice { NOTHING, EXIT, PLAY};

        // Function to check the player's click
            MenuChoice HandleClick(int x, int y);

        // Getters of variables
            sf::Texture const& getMainMenuImage() const { return m_mainMenuImage; }
            sf::Sprite const& getMainMenuSprite() const { return m_mainMenuSprite; }


    private:
        // The main menu's buttons' structure
            struct MenuButton
            {
                public:
                sf::Rect<int> rect; // The rectangle in which the player must click to perform the action
                MenuChoice action; // The action of the button
            };

        // List the buttons of the main menu
            std::list<MenuButton> m_menuButtons;

        // The appearance of the main menu
            sf::Texture m_mainMenuImage;
            sf::Sprite m_mainMenuSprite;

        sf::Rect<int> m_menuButtonRect; // So we don't create a new rectangle each time the player click
};

#endif
