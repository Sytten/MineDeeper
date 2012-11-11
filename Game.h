#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Character.h"
#include "CharacterMover.h"
#include "MainMenu.h"

class Game
{
    public:
        Game(int NbrTilesWidth, int NbrTilesHeight);
        ~Game();
        void start();

    private:
        void gameLoop();

        enum GameState { Uninitialized, Paused,
          ShowingMenu, Playing, Exiting };

        GameState m_gameState;
        sf::RenderWindow m_mainWindow;

        Map *m_map;
        Character *m_character;
        CharacterMover *m_characterMover;

    friend void draw(sf::RenderWindow &window, Game const& game);

};
#endif
