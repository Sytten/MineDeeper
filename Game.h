// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Game.h
// The header file of the Game object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

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
        // Main game loop
        void gameLoop();

        // Game state
        enum GameState { Uninitialized, Paused, ShowingMenu, Playing, Exiting };
            GameState m_gameState;

        // Main window
        sf::RenderWindow m_mainWindow;
            sf::Vector2<int> m_windowSize;

        // Game objects
        TilesMap m_tilesMap;
        Character m_character;
        KeyboardCharacterMover m_characterMover;
        Camera m_camera;
        Background m_background;

    // Draw can now access all the private variables of the class
    friend void draw(sf::RenderWindow &window, Game &game);

};
#endif
