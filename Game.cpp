// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Game.cpp
// Game is basically the engine of the game.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#include "Game.h"
#include "Draw.h"
#include <iostream>

Game::Game() : m_gameState(Uninitialized), m_windowSize(825, 750), m_tilesMap(75, 75), m_character(), m_characterMover(), m_camera(m_windowSize.x, m_windowSize.y), m_background("space.png", sf::Vector2f(0.5, 0.5))
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::start()
{
// We can only start if we are not in-game already
    if(m_gameState != Uninitialized)
        return;

// Create window and map
    m_mainWindow.create(sf::VideoMode((m_windowSize.x), (m_windowSize.y)), "MineDeeper Alpha V1.0.7.1", sf::Style::Close); //Create a window
        m_mainWindow.setFramerateLimit(60); //Limit the framerate, temporary!!!
        m_tilesMap.create(); //Create our map

// Play the game
    m_gameState = Game::ShowingMenu; // Set the game state to show the menu
        gameLoop(); // Enter in the game loop

m_mainWindow.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::gameLoop()
{
// Create event and clock handler
    sf::Event currentEvent;
    sf::Clock clock;

// Main game loop
    while(m_gameState != Exiting) // Do until the player decided to stop the game
    {
        // Check the different game state
            switch(m_gameState)
            {
                // If the game state is to show menu
                    case Game::ShowingMenu :
                    {
                        MainMenu mainMenu;

                        // Handle the new events until we change the game state
                            while(m_gameState == ShowingMenu)
                            {
                                while(m_mainWindow.pollEvent(currentEvent))
                                {
                                    if(currentEvent.type == sf::Event::MouseButtonPressed)
                                    {
                                        // Check if the mouse click is in a rect (button)
                                            MainMenu::MenuChoice choice = mainMenu.HandleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);

                                        // Depending on the rect, play or exit
                                            if(choice == MainMenu::PLAY)
                                                m_gameState = Playing;

                                            if(choice == MainMenu::EXIT)
                                                m_gameState = Exiting;
                                    }

                                    if(currentEvent.type == sf::Event::Closed) // So we can always close the window
                                                m_gameState = Exiting;
                                }

                                        draw(m_mainWindow, mainMenu);
                                        m_mainWindow.display();
                            }
                            break;
                    }

                // If the game state is to play
                    case Game::Playing :
                    {
                        // Do until we handle all the events
                            while (m_mainWindow.pollEvent(currentEvent))
                            {
                                // Check each event
                                    switch (currentEvent.type)
                                    {
                                        // If the player want to quit
                                            case sf::Event::Closed :
                                                {
                                                m_gameState = Exiting;
                                                break;
                                                }

                                        // When a key is pressed
                                            case sf::Event::KeyPressed:
                                                switch(currentEvent.key.code)
                                                {
                                                    // If UP arrow or W is pressed add NORTH direction
                                                        case sf::Keyboard::Up:
                                                        case sf::Keyboard::W:
                                                            m_characterMover.addDirection(KeyboardCharacterMover::NORTH);
                                                            break;

                                                    // If DOWN arrow or S is pressed add SOUTH direction
                                                        case sf::Keyboard::Down:
                                                        case sf::Keyboard::S:
                                                            m_characterMover.addDirection(KeyboardCharacterMover::SOUTH);
                                                            break;

                                                    // If LEFT arrow or A is pressed add WEST direction
                                                        case sf::Keyboard::Left:
                                                        case sf::Keyboard::A:
                                                            m_characterMover.addDirection(KeyboardCharacterMover::WEST);
                                                            break;

                                                    // If RIGHT arrow or D is pressed add EAST direction
                                                        case sf::Keyboard::Right:
                                                        case sf::Keyboard::D:
                                                            m_characterMover.addDirection(KeyboardCharacterMover::EAST);
                                                            break;

                                                    // We can return to the main menu
                                                        case sf::Keyboard::Escape:
                                                            m_gameState = ShowingMenu;
                                                            break;

                                                    default:
                                                        break;
                                                }
                                                break;

                                        // When a key is released
                                            case sf::Event::KeyReleased:
                                                switch(currentEvent.key.code)
                                                {
                                                    // If UP arrow or W is released remove NORTH direction
                                                        case sf::Keyboard::Up:
                                                        case sf::Keyboard::W:
                                                            m_characterMover.removeDirection(KeyboardCharacterMover::NORTH);
                                                            break;

                                                    // If DOWN arrow or S is released remove SOUTH direction
                                                        case sf::Keyboard::Down:
                                                        case sf::Keyboard::S:
                                                            m_characterMover.removeDirection(KeyboardCharacterMover::SOUTH);
                                                            break;

                                                    // If LEFT arrow or A is released remove WEST direction
                                                        case sf::Keyboard::Left:
                                                        case sf::Keyboard::A:
                                                            m_characterMover.removeDirection(KeyboardCharacterMover::WEST);
                                                            break;

                                                    // If RIGHT arrow or D is released remove EAST direction
                                                        case sf::Keyboard::Right:
                                                        case sf::Keyboard::D:
                                                            m_characterMover.removeDirection(KeyboardCharacterMover::EAST);
                                                            break;

                                                    default:
                                                        break;
                                                }
                                                break;

                                        default:
                                            break;
                                        }
                                    }

                                // Move the character
                                    m_characterMover.move(m_mainWindow, m_character, m_tilesMap, m_camera, m_background, clock.restart());

                                // Display all the objects
                                    m_mainWindow.clear();
                                    draw(m_mainWindow, *this);
                                    m_mainWindow.display();

                                break;
                            }
                default:
                    break;
            }
    }
}
