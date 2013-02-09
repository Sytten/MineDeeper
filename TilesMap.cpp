// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TilesMap.cpp
// TilesMap manages the game map. It creates a new one, loads the tileset and
// manages the map variables (tile size, world size, etc.).
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 01/02/2013
// ---------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "TilesMap.h"
#include "ImageException.h"

using namespace std;

TilesMap::TilesMap(int tileSizeX, int tileSizeY) : m_tileSize(tileSizeX, tileSizeY)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TilesMap::create()
{
// When we create the map, we have to load the tileset and the map
    loadLevel();
    loadTileSet();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TilesMap::loadTileSet()
{
// Load the tileset
    if(!m_tileSet.loadFromFile("tilesetmap.png"))
        throw ImageException("tilesetmap.png"); // Throw an error if we can't

// Set the tile's texture
    m_tile.setTexture(m_tileSet);

// Calculate the tileset size (in terms of tiles)
    m_tileSetSize.x = (m_tileSet.getSize().x/m_tileSize.x);
    m_tileSetSize.y = (m_tileSet.getSize().y/m_tileSize.y);

// Open the tile configuration file
    ifstream tileConfig("tile.config");

// Check if the file really opened
    if(tileConfig.is_open() && !tileConfig.eof())
    {
        TileProp tile;
        int numTile(0);
        string testValue;
        string line;
        string word;
        vector<string> words;
        ostringstream convert;

        // Check the properties for each tile
            for(int y(0); y < m_tileSetSize.y; y++)
            {
                for(int x(0); x < m_tileSetSize.x; x++)
                {
                    // Find the place in the tileset
                        tile.posInTileSet.width = m_tileSize.y;
                        tile.posInTileSet.height = m_tileSize.x;
                        tile.posInTileSet.left = x*m_tileSize.x;
                        tile.posInTileSet.top = y*m_tileSize.y;

                    // Get a line in the configuration file
                        getline(tileConfig, line);

                    // If the line start with a # or \n or is empty, get a new one
                        while(line.at(0) == '#' || line.at(0) == '\n' || line.empty())
                        {
                            line.clear();
                            getline(tileConfig, line);
                        }

                    // Erase the spaces and the tabs
                        line.erase(remove(line.begin(), line.end(), ' '), line.end());
                        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

                    // Take the ID of the tile we are working with
                        word = line.substr(0, line.find(';'));
                            line.erase(0, line.find(';')+1);
                            convert << numTile; // Convert it to a string
                            testValue = convert.str();
                            convert.str(string());

                    // Check if the ID is good, if not: stop the game
                        if(testValue != word)
                            throw "Error in the tiles' configuration file";

                    // Check each word in the line
                        while(line.length() != 0)
                        {
                            word = line.substr(0, line.find(';'));
                            line.erase(0, line.find(';')+1);
                            words.push_back(word);
                        }

                    // If we don't have enough words, stop the game
                        if(words.size() < 4)
                            throw "Error in the tiles' configuration file";

                    // Set the properties of the tile
                        if(words.at(0) == "false")
                            tile.walkable = false;
                        else
                            tile.walkable = true;

                        if(words.at(1) == "false")
                            tile.diggable = false;
                        else
                            tile.diggable = true;

                        if(words.at(2) == "false")
                            tile.ore = false;
                        else
                            tile.ore = true;

                        if(words.at(3) == "false")
                            tile.door = false;
                        else
                            tile.door = true;

                    // Put the tile in a map, so we can access it later
                        m_tilesProps[numTile] = tile;

                    // Increase the number of the tile by 1 (so we don't override what we did)
                        ++numTile;

                    // Clear our variables
                        line.clear();
                        testValue.clear();
                        word.clear();
                        words.clear();
                }
            }

    // Close the file
        tileConfig.close();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                m_world[x][y] = 1;
        }
    }

    m_worldSize.x = m_world.size() * m_tileSize.x;
    for(int i = 0; i < (int)m_world[0].size() ; i++)
    {
           m_worldSize.y += m_tileSize.y;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TilesMap::TileProp TilesMap::getTileProp(int tile) const
{
// Return the properties of the specified tile
    return m_tilesProps.at(tile);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TilesMap::setTile(int x, int y, int blockID)
{
// Set the ID of the tile at the specified location
    m_world[x][y] = blockID;
}
