// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Draw.h
// The header file of the draw module. See the cpp file for more
// information about the module.
//
// Author: Sytten
// Creation date: 07/11/2012
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../mapping/TilesMap.h"
#include "../character/Character.h"
#include "../gui/MainMenu.h"
#include "Camera.h"

void draw(sf::RenderWindow &window, const MainMenu &mainMenu);
void draw(sf::RenderWindow &window, Character &character, sf::Vector2f cameraPos);
void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera);
void draw(sf::RenderWindow &window, const Background &background);
void draw(sf::RenderWindow &window, Game &game);

#endif
