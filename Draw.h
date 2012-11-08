#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Game.h"
#include "Character.h"

void draw(sf::RenderWindow &window, const Character *character);
void draw(sf::RenderWindow &window, const Map *map);
void draw(sf::RenderWindow &window, const Game &game);

#endif
