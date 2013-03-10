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
// Last modification date: 18/02/2013
// ---------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "TilesMap.h"
#include "Character.h"
#include "KeyboardCharacterMover.h"
#include "Camera.h"
#include "MainMenu.h"
#include "Background.h"
#include "FuelBuilding.h"
#include "SellBuilding.h"
#include "Collisions.h"
#include "Building.h"
#include "Filter.h"

class Game
{
    public:
        Game();

        // Main game loop
            void gameLoop();

    private:
        // Game states loops
            void playLoop(sf::Event& currentEvent, sf::Clock& clock);
            void mainMenuLoop(sf::Event& currentEvent);
            void pausedLoop(sf::Event& currentEvent);
            void enterBuilding();
            void gameOver();

        // Game states
            enum GameState { Uninitialized, Paused, ShowingMenu, Playing, Exiting };
                GameState m_gameState;

        // Main window
            sf::RenderWindow m_mainWindow;
                sf::Vector2f m_windowSize;

        // Main menu object
            std::unique_ptr<MainMenu> m_mainMenu;

        // Game objects
            std::unique_ptr<TilesMap> m_tilesMap;
            std::unique_ptr<Character> m_character;
            std::unique_ptr<KeyboardCharacterMover> m_characterMover;
                std::unique_ptr<Collisions> m_collisions;
            std::unique_ptr<Camera> m_camera;
            std::unique_ptr<Background> m_background;
            sfg::SFGUI m_sfgui;
                std::vector< std::unique_ptr<Building> > m_buildings;

        // Paused and Game over objects
            sf::Text m_text;
            sf::Font m_eastwoodFont;
            std::unique_ptr<Filter> m_gameOverfilter;
            sf::RectangleShape m_pausedFilter;

    // Draw can now access all the private variables of the class
        friend void draw(sf::RenderWindow &window, Game &game);

};
#endif
