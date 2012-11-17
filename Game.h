#ifndef GAME_H
#define GAME_H

#include <utility>

#include <SFML/Graphics.hpp>

#include "TilesMap.h"
#include "Character.h"
#include "CharacterMover.h"
#include "MainMenu.h"

class Game
{
    public:
        Game();
        void start();

    private:
        void gameLoop();

        enum GameState { Uninitialized, Paused,
          ShowingMenu, Playing, Exiting };

        GameState m_gameState;
        sf::RenderWindow m_mainWindow;

        TilesMap m_tilesMap;
        Character m_character;
        CharacterMover m_characterMover;

        sf::Texture m_background;

    friend void draw(sf::RenderWindow &window, Game const& game);

};
#endif
