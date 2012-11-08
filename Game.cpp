#include "Game.h"

Game::Game(int NbrTilesWidth, int NbrTilesHeight)
{
    map = new Map(NbrTilesWidth, NbrTilesHeight);
    character = new Character();
}

Game::~Game()
{
    delete map;
        map = 0;
    delete character;
        character = 0;
}

void Game::createMap()
{
    map->create();
}
