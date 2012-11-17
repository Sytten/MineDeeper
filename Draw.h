#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

#include "TilesMap.h"
#include "Game.h"
#include "Character.h"
#include "MainMenu.h"

void draw(sf::RenderWindow &window, const MainMenu &mainMenu);
void draw(sf::RenderWindow &window, const Character &character);
void draw(sf::RenderWindow &window, const TilesMap &tilesMap);
void draw(sf::RenderWindow &window, const Game &game);

#endif
