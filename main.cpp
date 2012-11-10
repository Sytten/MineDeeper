#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Draw.h"
#include "CharacterMover.h"

int main()
{
    //define the tiles of the game
    const unsigned int WIDTH_TILE = 75;
    const unsigned int HEIGHT_TILE = 75;
    const unsigned int NBR_TILES_WIDTH = 11;
    const unsigned int NBR_TILES_HEIGHT = 10;

    //Create basic window, map, mover and direction of the player
    sf::RenderWindow window(sf::VideoMode(825, 750), "MineDeeper", sf::Style::Close);
    Game game(NBR_TILES_WIDTH, NBR_TILES_HEIGHT);
    game.createMap();
    CharacterMover charactermover;
    Direction direction = NONE; //to send direction when a key is pressed

    bool playing = true;
    sf::Clock clock;
    sf::Event event;

    //Start game loop
    while (playing)
    {
        while (window.pollEvent(event)) //check the events
        {
            switch (event.type)
            {
                case sf::Event::Closed : //if the player want to quit
                    playing = false;
                    break;

                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Up:
                        case sf::Keyboard::W:
                            direction = NORTH;
                            charactermover.addDirection(direction);
                            break;

                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            direction = SOUTH;
                            charactermover.addDirection(direction);
                            break;

                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            direction = WEST;
                            charactermover.addDirection(direction);
                            break;

                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            direction = EAST;
                            charactermover.addDirection(direction);
                            break;
                    }
                    break;

                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Up:
                        case sf::Keyboard::W:
                            direction = NORTH;
                            charactermover.removeDirection(direction);
                            break;

                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            direction = SOUTH;
                            charactermover.removeDirection(direction);
                            break;

                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            direction = WEST;
                            charactermover.removeDirection(direction);
                            break;

                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            direction = EAST;
                            charactermover.removeDirection(direction);
                            break;
                    }
                    break;
            }

            direction = NONE;

        }

        if(clock.getElapsedTime().asMilliseconds() > 6.f)
        {
            clock.restart();
            charactermover.move(game.returnCharacter());
        }

        window.clear();
        draw(window, game);
        window.display();
    }

    return 0;
}
