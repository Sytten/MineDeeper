#include "Game.h"
#include "Draw.h"

Game::Game(int NbrTilesWidth, int NbrTilesHeight)
{
    m_gameState = Uninitialized;

    m_map = new Map(NbrTilesWidth, NbrTilesHeight);
    m_character = new Character();
    m_characterMover = new CharacterMover();
}

Game::~Game()
{
    delete m_map;
        m_map = 0;
    delete m_character;
        m_character = 0;
    delete m_characterMover;
        m_characterMover = 0;
}


void Game::start()
{
    if(m_gameState != Uninitialized) //we can only start if we are not in-game already
        return;

    m_mainWindow.create(sf::VideoMode(825, 750), "MineDeeper", sf::Style::Close); //window is not resizable

    m_map->create();

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
                                    m_characterMover->addDirection(CharacterMover::NORTH);
                                    break;

                                case sf::Keyboard::Down:
                                case sf::Keyboard::S:
                                    m_characterMover->addDirection(CharacterMover::SOUTH);
                                    break;

                                case sf::Keyboard::Left:
                                case sf::Keyboard::A:
                                    m_characterMover->addDirection(CharacterMover::WEST);
                                    break;

                                case sf::Keyboard::Right:
                                case sf::Keyboard::D:
                                    m_characterMover->addDirection(CharacterMover::EAST);
                                    break;

                                case sf::Keyboard::Escape:
                                    m_gameState = ShowingMenu;
                                    break;
                            }
                            break;

                        case sf::Event::KeyReleased: //when a key (aswd or arrows) is released, remove the direction so we don't move the character
                            switch(currentEvent.key.code)
                            {
                                case sf::Keyboard::Up:
                                case sf::Keyboard::W:
                                    m_characterMover->removeDirection(CharacterMover::NORTH);
                                    break;

                                case sf::Keyboard::Down:
                                case sf::Keyboard::S:
                                    m_characterMover->removeDirection(CharacterMover::SOUTH);
                                    break;

                                case sf::Keyboard::Left:
                                case sf::Keyboard::A:
                                    m_characterMover->removeDirection(CharacterMover::WEST);
                                    break;

                                case sf::Keyboard::Right:
                                case sf::Keyboard::D:
                                    m_characterMover->removeDirection(CharacterMover::EAST);
                                    break;
                            }
                            break;
                        }
                    }

                if(clock.getElapsedTime().asMilliseconds() > 6.f) //each 6 millisecond we move the character
                {
                    clock.restart();
                    m_characterMover->move(m_character);
                }

                m_mainWindow.clear();
                draw(m_mainWindow, *this);
                m_mainWindow.display();

                break;
                }
        }
    }
}
