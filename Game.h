#ifndef GAME_H
#define GAME_H

#include <utility>

#include <SFML/Graphics.hpp>

#include "TilesMap.h"
#include "Character.h"
#include "KeyboardCharacterMover.h"
#include "Camera.h"
#include "MainMenu.h"
#include "Background.h"

class Game
{
    public:
        Game();
        void start();

    private:
        void gameLoop();

        enum GameState { Uninitialized, Paused, ShowingMenu, Playing, Exiting };
        GameState m_gameState;

        sf::RenderWindow m_mainWindow;
        sf::Vector2<int> m_windowSize;

        TilesMap m_tilesMap;
        Character m_character;
        KeyboardCharacterMover m_characterMover;
        Camera m_camera;

        Background m_background;

    friend void draw(sf::RenderWindow &window, Game &game);

};
#endif
