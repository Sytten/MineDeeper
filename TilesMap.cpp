#include "TilesMap.h"

TilesMap::TilesMap() : m_tileSize(75, 75), m_tileSetSize(3, 1)
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

    for(int i(0); i < m_tileSetSize.y; i++)
    {
        for(int j(0); j < m_tileSetSize.x; j++)
        {
            TileProp tile;

            tile.posInTileSet.width = m_tileSize.y;
            tile.posInTileSet.height = m_tileSize.x;
            tile.posInTileSet.left = j*m_tileSize.x;
            tile.posInTileSet.top = i*m_tileSize.y;

            if(nbrTile ==  0)
                tile.walkable = true;

            else
                tile.walkable = false;

            m_tilesProps[nbrTile] = tile;

            nbrTile++;
        }
    }
}


void TilesMap::loadLevel()
{
    int y, x;

    m_world.resize(20);

    for(int i = 0; i < (int)m_world.size(); i++)
    {
        m_world.at(i).resize(15, 0);
    }

    for(x = 0; x < (int)m_world.size(); x++)
    {
        for(y = 0; y < (int)m_world[x].size(); y++)
        {
            if(y < 9)
                m_world[x][y] = 0;

            else
                m_world[x][y] = 2;
        }
    }

    m_worldSize.x = m_world.size() * m_tileSize.x;
    for(int i = 0; i < (int)m_world[0].size() ; i++)
    {
           m_worldSize.y += m_tileSize.y;
    }
}


TilesMap::TileProp TilesMap::getTileProp(int tile) const
{

    return m_tilesProps.at(tile); //return the props of the specified tile
}
