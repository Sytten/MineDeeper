// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// MainMenu.cpp
// MainMenu manages the menu you see when you start the game. It handles the
// user's clicks.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "MainMenu.h"
#include "../exceptions/ImageException.h"

MainMenu::MainMenu()
{
// Load the image of the main menu
    if(!m_mainMenuImage.loadFromFile("data/mainmenu.png"))
        throw ImageException("mainemenu.png"); // If it fails, throw an error

// Set the sprite texture
    m_mainMenuSprite.setTexture(m_mainMenuImage);

// Create the rectangles for the buttons of the main menu
    MenuButton playButton;
        playButton.rect.left = 100;
        playButton.rect.top = 100;
        playButton.rect.width = 625;
        playButton.rect.height = 230;
        playButton.action = PLAY;

    MenuButton exitButton;
        exitButton.rect.left = 100;
        exitButton.rect.top = 420;
        exitButton.rect.width = 625;
        exitButton.rect.height = 230;
        exitButton.action = EXIT;

// Put the rectangles in a list to be able access them later
    m_menuButtons.push_back(playButton);
    m_menuButtons.push_back(exitButton);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MainMenu::MenuChoice MainMenu::HandleClick(int x, int y)
{
// Create an iterator to run through the list of buttons
    std::list<MenuButton>::iterator it;

// Check if the player clicked on a button
    for( it = m_menuButtons.begin(); it != m_menuButtons.end(); ++it)
    {
        m_menuButtonRect = (*it).rect;
        if(x > m_menuButtonRect.left && x < (m_menuButtonRect.left + m_menuButtonRect.width) && y > m_menuButtonRect.top && y < (m_menuButtonRect.top + m_menuButtonRect.height))
           return (*it).action; // Return the action of the button
    }

    return NOTHING; //else return nothing
}
