#include "MainMenu.h"

MainMenu::MainMenu()
{
    m_mainMenuImage.loadFromFile("mainmenu.png"); //load our Main menu image

    //create the rects for the main menu buttons
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

    //put the rects in a list to acces them later
    m_menuButtons.push_back(playButton);
    m_menuButtons.push_back(exitButton);
}


MainMenu::MenuChoice MainMenu::HandleClick(int x, int y)
{
    std::list<MenuButton>::iterator it;

    for( it = m_menuButtons.begin(); it != m_menuButtons.end(); it++) //with the iterator check the rects (in the list)
    {
        sf::Rect<int> menuButtonRect = (*it).rect;
        if(x > menuButtonRect.left && x < (menuButtonRect.left + menuButtonRect.width) && y > menuButtonRect.top && y < (menuButtonRect.top + menuButtonRect.height)) //if the player clicked on a button
           return (*it).action; //return the action on the this button
    }

    return NOTHING; //else return nothing
}
