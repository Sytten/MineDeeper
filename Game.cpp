#include "Game.h"
#include "Draw.h"

Game::Game() : m_gameState(Uninitialized), m_windowSize(825, 750), m_tilesMap(), m_character(), m_characterMover(), m_camera(m_windowSize.x, m_windowSize.y)
{
    m_background.loadFromFile("space.png");
}


void Game::start()
{
    if(m_gameState != Uninitialized) //we can only start if we are not in-game already
        return;

    m_mainWindow.create(sf::VideoMode((m_windowSize.x), (m_windowSize.y)), "MineDeeper", sf::Style::Close); //window is not resizable

    m_tilesMap.create();

    m_gameState = Game::ShowingMenu;

    gameLoop(); //enter in the game loop

    m_mainWindow.close();
}


void Game::gameLoop()
{
    sf::Event currentEvent;
    sf::Clock clock;

    while(m_gameState != Exiting) //do until the player decided to stop the game
    {
        switch(m_gameState)
        {
            case Game::ShowingMenu: //if the game state is to show menu
                {
                MainMenu mainMenu;
                while(m_gameState == ShowingMenu) //until we change the game state
                {
                    while(m_mainWindow.pollEvent(currentEvent))
                    {
                        if(currentEvent.type == sf::Event::MouseButtonPressed)
                        {
                            MainMenu::MenuChoice choice = mainMenu.HandleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y); //check if the mouse click is in a rect

                            //depending on the rect, play or exit
                            if(choice == MainMenu::PLAY)
                                m_gameState = Playing;

                            if(choice == MainMenu::EXIT)
                                m_gameState = Exiting;
                        }

                        if(currentEvent.type == sf::Event::Closed) //so we can always close the window
                            m_gameState = Exiting;
                    }

                    draw(m_mainWindow, mainMenu);
                    m_mainWindow.display();
                }
                break;
                }

            case Game::Playing: //if the game state is to play
                {

                while (m_mainWindow.pollEvent(currentEvent)) //check the events
                    {
                    switch (currentEvent.type)
                    {
                        case sf::Event::Closed : //if the player want to quit
                            {
                            m_gameState = Exiting;
                            break;
                            }

                        case sf::Event::KeyPressed: //when a key (aswd or arrows) is pressed, add the direction so we can move the character
                            switch(currentEvent.key.code)
                            {
                                case sf::Keyboard::Up:
                                case sf::Keyboard::W:
                                    m_characterMover.addDirection(KeyboardCharacterMover::NORTH);
                                    break;

                                case sf::Keyboard::Down:
                                case sf::Keyboard::S:
                                    m_characterMover.addDirection(KeyboardCharacterMover::SOUTH);
                                    break;

                                case sf::Keyboard::Left:
                                case sf::Keyboard::A:
                                    m_characterMover.addDirection(KeyboardCharacterMover::WEST);
                                    break;

                                case sf::Keyboard::Right:
                                case sf::Keyboard::D:
                                    m_characterMover.addDirection(KeyboardCharacterMover::EAST);
                                    break;

                                case sf::Keyboard::Escape:
                                    m_gameState = ShowingMenu;
                                    break;

                                default:
                                    break;
                            }
                            break;

                        case sf::Event::KeyReleased: //when a key (aswd or arrows) is released, remove the direction so we don't move the character
                            switch(currentEvent.key.code)
                            {
                                case sf::Keyboard::Up:
                                case sf::Keyboard::W:
                                    m_characterMover.removeDirection(KeyboardCharacterMover::NORTH);
                                    break;

                                case sf::Keyboard::Down:
                                case sf::Keyboard::S:
                                    m_characterMover.removeDirection(KeyboardCharacterMover::SOUTH);
                                    break;

                                case sf::Keyboard::Left:
                                case sf::Keyboard::A:
                                    m_characterMover.removeDirection(KeyboardCharacterMover::WEST);
                                    break;

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

                m_characterMover.move(m_character, m_tilesMap, m_camera, clock.restart());

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
