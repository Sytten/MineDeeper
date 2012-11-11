#include "Map.h"

Map::Map(int NbrTilesWidth, int NbrTilesHeight) : m_nbrTilesWidth(NbrTilesWidth), m_nbrTilesHeight(NbrTilesHeight)
{
    //Load textures
    sky.loadFromFile("sky.png");
    land.loadFromFile("land.png");
}

void Map::create()
{
    table.reserve(110); //I need 110 squares

    for(int i(0); i < 88; i++) //In my map I want sky(0) and land(1)
        table.push_back(0);

    for(int i(0); i < 22; i++)
        table.push_back(1);
}
