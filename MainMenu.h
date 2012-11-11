#ifndef MAINMENU_H
#define MAINMENU_H

#include <List>

#include <SFML/Graphics.hpp>

class MainMenu
{
    public:
        MainMenu();

        enum MenuChoice { NOTHING, EXIT, PLAY};

        MenuChoice HandleClick(int x, int y);


    private:
        struct MenuButton
        {
            public:
            sf::Rect<int> rect;
            MenuChoice action;
        };

        std::list<MenuButton> m_menuButtons;

        sf::Texture m_mainMenuImage;

        friend void draw(sf::RenderWindow &window, const MainMenu &mainMenu);
};

#endif
