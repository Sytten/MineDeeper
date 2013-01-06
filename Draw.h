#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

#include "TilesMap.h"
#include "Game.h"
#include "Character.h"
#include "MainMenu.h"
#include "Camera.h"

void draw(sf::RenderWindow &window, const MainMenu &mainMenu);
void draw(sf::RenderWindow &window, Character &character, sf::Vector2f cameraPos);
void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera);
void draw(sf::RenderWindow &window, const Background &background);
void draw(sf::RenderWindow &window, Game &game);

#endif
