#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

class Game
{
    public:
    Game(int NbrTilesWidth, int NbrTilesHeight);
    ~Game();
    void createMap();

    private:
    Map *map;
    Character *character;

    friend void draw(sf::RenderWindow &window, Game const& game);

};
#endif
