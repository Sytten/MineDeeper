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
// Last modification date: 06/03/2013
// ---------------------------------------------------------------------------

#include "Game.h"
#include "Draw.h"

Game::Game() : m_gameState(Uninitialized), m_windowSize(825, 750)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::gameLoop()
{
// We can only start if we are not in-game already
    if(m_gameState != Uninitialized)
        return;

// Create the window
    m_mainWindow.create(sf::VideoMode((m_windowSize.x), (m_windowSize.y)), "MineDeeper Alpha V1.0.8", sf::Style::Close); //Create a window
        m_mainWindow.setFramerateLimit(60); //Limit the framerate, temporary!!!

// Create event and clock handler
    sf::Event currentEvent;
    sf::Clock clock;

// Play the game
    m_gameState = Game::ShowingMenu; // Set the game state to show the menu

// Main game loop
    while(m_gameState != Exiting) // Do until the player decided to stop the game
    {
        // Check the different game state
            switch(m_gameState)
            {
                // If the game state is to show menu
                    case Game::ShowingMenu :
                    {
                        mainMenuLoop(currentEvent);
                        break;
                    }

                // If the game state is to play
                    case Game::Playing :
                    {
                        playLoop(currentEvent, clock);
                        break;
                    }

                // Else, do nothing
                    default:
                        break;
            }
    }

// Quit the game
    m_mainWindow.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::mainMenuLoop(sf::Event& currentEvent)
{
// Create the Main menu object
    m_mainMenu.reset( new MainMenu );

// Handle the new events until we change the game state
    while(m_gameState == ShowingMenu)
    {
        while(m_mainWindow.pollEvent(currentEvent))
        {
            if(currentEvent.type == sf::Event::MouseButtonPressed)
            {
                // Check if the mouse click is in a rect (button)
                    MainMenu::MenuChoice choice = m_mainMenu->HandleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);

                // Depending on the rect, play or exit
                    if(choice == MainMenu::PLAY)
                        m_gameState = Playing;

                    if(choice == MainMenu::EXIT)
                        m_gameState = Exiting;
            }

            if(currentEvent.type == sf::Event::Closed) // So we can always close the window
                m_gameState = Exiting;
        }

        draw(m_mainWindow, *(m_mainMenu));
        m_mainWindow.display();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::playLoop(sf::Event& currentEvent, sf::Clock& clock)
{
// Create games objects
    m_tilesMap.reset( new TilesMap(75, 75) );
    m_character.reset( new Character );
    m_characterMover.reset( new KeyboardCharacterMover );
    m_collisions.reset( new Collisions );
    m_camera.reset( new Camera(m_windowSize.x, m_windowSize.y) );
    m_background.reset( new Background("space.png", sf::Vector2f(0.5, 0.5)) );
    m_buildings.clear();
        m_buildings.push_back( std::unique_ptr<Building>(new FuelBuilding(m_windowSize, 1)) );
        m_buildings.push_back( std::unique_ptr<Building>(new SellBuilding(m_windowSize, 2)) );
    m_gameOverfilter.reset( new Filter(sf::Color::Black, 1.f, sf::Rect<float>(0, 0, m_windowSize.x, m_windowSize.y) , true, 0.02f) );
    sf::Clock fuelClock;

// Set the properties of different objects
    m_pausedFilter.setFillColor(sf::Color(0, 0, 0, 100));
    m_pausedFilter.setSize(m_windowSize);

    m_eastwoodFont.loadFromFile("data/Eastwood.ttf");
        m_text.setFont(m_eastwoodFont);
        m_text.setCharacterSize(70);


// Do until we want to exit the game
    while (m_gameState == Game::Playing)
    {
        // Do until we handle all the events
            while (m_mainWindow.pollEvent(currentEvent))
            {
                // Check each event
                    switch (currentEvent.type)
                    {
                        // If the player want to quit
                            case sf::Event::Closed :
                                m_gameState = Exiting;
                                break;

                        // When a key is pressed
                            case sf::Event::KeyPressed:
                                switch(currentEvent.key.code)
                                {
                                    // If UP arrow or W is pressed add NORTH direction
                                        case sf::Keyboard::Up:
                                        case sf::Keyboard::W:
                                            m_characterMover->addDirection(KeyboardCharacterMover::NORTH);
                                            break;

                                    // If DOWN arrow or S is pressed add SOUTH direction
                                        case sf::Keyboard::Down:
                                        case sf::Keyboard::S:
                                            m_characterMover->addDirection(KeyboardCharacterMover::SOUTH);
                                            break;

                                    // If LEFT arrow or A is pressed add WEST direction
                                        case sf::Keyboard::Left:
                                        case sf::Keyboard::A:
                                            m_characterMover->addDirection(KeyboardCharacterMover::WEST);
                                            break;

                                    // If RIGHT arrow or D is pressed add EAST direction
                                        case sf::Keyboard::Right:
                                        case sf::Keyboard::D:
                                            m_characterMover->addDirection(KeyboardCharacterMover::EAST);
                                            break;

                                    // If ESC is pressed, return to the main menu
                                        case sf::Keyboard::Escape:
                                            gameOver();
                                            break;

                                    // If P is pressed, paused the game
                                        case sf::Keyboard::P:
                                            m_gameState = Game::Paused;
                                            pausedLoop(currentEvent);
                                            clock.restart();
                                            fuelClock.restart();
                                            break;

                                    // If enter pressed, check if the player can enter in a building
                                        case sf::Keyboard::Return:
                                            enterBuilding();
                                                clock.restart();
                                                fuelClock.restart();
                                            m_characterMover->checkStateOfKeys();
                                            break;

                                    // Else, do nothing
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
                                            m_characterMover->removeDirection(KeyboardCharacterMover::NORTH);
                                            break;

                                    // If DOWN arrow or S is released remove SOUTH direction
                                        case sf::Keyboard::Down:
                                        case sf::Keyboard::S:
                                            m_characterMover->removeDirection(KeyboardCharacterMover::SOUTH);
                                            break;

                                    // If LEFT arrow or A is released remove WEST direction
                                        case sf::Keyboard::Left:
                                        case sf::Keyboard::A:
                                            m_characterMover->removeDirection(KeyboardCharacterMover::WEST);
                                            break;

                                    // If RIGHT arrow or D is released remove EAST direction
                                        case sf::Keyboard::Right:
                                        case sf::Keyboard::D:
                                            m_characterMover->removeDirection(KeyboardCharacterMover::EAST);
                                            break;

                                    // Else, do nothing
                                        default:
                                            break;
                                }
                                break;

                        // Else, do nothing
                            default:
                                break;
                    }
            }
        // Move the character
            m_characterMover->move(m_mainWindow, *(m_character), *(m_collisions), *(m_tilesMap), *(m_camera), *(m_background), clock.restart());

        // Remove fuel each 10 seconds
        if(fuelClock.getElapsedTime().asSeconds() > 10)
        {
            m_character->getFuel().removeFuel(1);
            fuelClock.restart();
        }

        // Check if the player is still alive and have fuel
            if(!m_character->getLife().isAlive())
                gameOver();

            if(m_character->getFuel().isEmpty())
                gameOver();

        // Check if the player have found all the artifacts
            if(m_character->getArtifacts().allFound())
                m_gameState = Game::ShowingMenu;

        // Display all the objects
        if(m_gameState == Game::Playing)
        {
            m_mainWindow.clear();
            draw(m_mainWindow, *this);
            m_mainWindow.display();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::pausedLoop(sf::Event& currentEvent)
{
// Set the properties
    m_text.setString("Paused!");
        m_text.setColor(sf::Color::White);
        m_text.setPosition((m_windowSize.x/2) - (m_text.getLocalBounds().width/2), (m_windowSize.y/2) - (m_text.getLocalBounds().height/2));

// Display paused text
    m_mainWindow.draw(m_pausedFilter);
    m_mainWindow.draw(m_text);
    m_mainWindow.display();

// Do while the game state is set to paused
    while(m_gameState == Game::Paused)
    {
        while(m_mainWindow.pollEvent(currentEvent))
        {
            if(currentEvent.type == sf::Event::KeyPressed)
            {
                // If P is pressed, depaused the game
                    if(currentEvent.key.code == sf::Keyboard::P)
                        m_gameState = Game::Playing;
                // If ESC is pressed, return to the main menu
                    if(currentEvent.key.code == sf::Keyboard::Escape)
                        m_gameState = Game::ShowingMenu;
            }

            if(currentEvent.type == sf::Event::Closed) // So we can always close the window
                m_gameState = Exiting;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::enterBuilding()
{
// Check if the player collided with a building (and a door), it return the ID of the building (or 0 if we don`t collided)
    unsigned buildingID = m_collisions->collidedBuilding(m_character->getCharacterRect(), (*m_tilesMap));

// If the ID is not 0, check the building that have this ID
    if(buildingID != 0)
    {
        for(std::vector< std::unique_ptr<Building> >::iterator iter(m_buildings.begin()); iter != m_buildings.end(); ++iter)
        {
            if((*iter)->getID() == buildingID)
                (*iter)->enter(m_sfgui, m_mainWindow, m_character.get());
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::gameOver()
{
// Set the properties
    m_text.setString("Game Over!");
        m_text.setColor(sf::Color::Red);
        m_text.setPosition((m_windowSize.x/2) - (m_text.getLocalBounds().width/2), (m_windowSize.y/2) - (m_text.getLocalBounds().height/2));

// While the alpha is less than 90
    while(m_gameOverfilter->getAlpha() < 90)
    {
        m_gameOverfilter->runFilter();
        m_mainWindow.draw(m_gameOverfilter->getFilter());
        m_mainWindow.draw(m_text);
        m_mainWindow.display();
        // !!!Important!!! We don't clear the screen, so the filter is applied on the last one!
    }

// Change the gameState to return to the menu
    m_gameState = Game::ShowingMenu;
}
