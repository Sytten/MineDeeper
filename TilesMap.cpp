#include "TilesMap.h"

TilesMap::TilesMap() : m_tileWidth(75), m_tileHeight(75), m_worldWidth(825), m_worldHeight(750), m_nbrTilesX(3), m_nbrTilesY(1)
{
}

void TilesMap::create()
{
    loadLevel();
    loadTileSet();
}


void TilesMap::loadTileSet()
{
    m_tileSet.loadFromFile("tilesetmap.png");

    int nbrTile(0);

    for(int i(0); i < m_nbrTilesY; i++)
    {
        for(int j(0); j < m_nbrTilesX; j++)
        {
            TileProp tileProp;

            tileProp.tileRect.width = m_tileWidth;
            tileProp.tileRect.height = m_tileHeight;
            tileProp.tileRect.left = j*m_tileWidth;
            tileProp.tileRect.top = i*m_tileHeight;

            if(nbrTile ==  0)
                tileProp.full = false;

            else
                tileProp.full = true;

            m_tilesProps[nbrTile] = tileProp;

            nbrTile++;
        }
    }

}


void TilesMap::loadLevel()
{
    table.reserve(110); //I need 110 squares

    for(int i(0); i < 88; i++) //In my map I want sky(0) and background land(2)
        table.push_back(0);

    for(int i(0); i < 22; i++)
        table.push_back(2);
}


TilesMap::TileProp TilesMap::getTileProp(int tile) const
{
    return m_tilesProps.at(tile); //return the props of the specified tile
}
