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

#include "mapping/TilesMap.h"
#include "character/Character.h"
#include "character/KeyboardCharacterMover.h"
#include "render/Camera.h"
#include "render/Background.h"
#include "render/Filter.h"
#include "gui/MainMenu.h"
#include "buildings/Building.h"
#include "buildings/FuelBuilding.h"
#include "buildings/SellBuilding.h"
#include "buildings/UpgradeBuilding.h"
#include "mechanics/Collisions.h"
#include "sound/SFMLAudioProvider.h"
#include "ServiceLocator.h"

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
            void win();

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
            std::unique_ptr<Filter> m_winFilter;
            sf::RectangleShape m_pausedFilter;

    // Draw can now access all the private variables of the class
        friend void draw(sf::RenderWindow &window, Game &game);

};
#endif
