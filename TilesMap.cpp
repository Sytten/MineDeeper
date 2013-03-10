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
// Last modification date: 09/03/2013
// ---------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "TilesMap.h"
#include "ImageException.h"
#include "TileException.h"
#include "WorldException.h"

using namespace std;

TilesMap::TilesMap(int tileSizeX, int tileSizeY) : m_tileSize(tileSizeX, tileSizeY)
{
// When we create the map, we have to load the tileset and the map
    loadTileSet();
    loadLevel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TilesMap::loadTileSet()
{
// Load the tileset
    if(!m_tileSet.loadFromFile("data/tilesetmap.png"))
        throw ImageException("tilesetmap.png"); // Throw an error if we can't

// Set the tile's texture
    m_tile.setTexture(m_tileSet);

// Calculate the tileset size (in terms of tiles)
    m_tileSetSize.x = (m_tileSet.getSize().x/m_tileSize.x);
    m_tileSetSize.y = (m_tileSet.getSize().y/m_tileSize.y);

// Open the tile configuration file
    ifstream tileConfig("data/tile.config");

// Check if the file really opened
    if(tileConfig.is_open() && !tileConfig.eof())
    {
        try
        {
            sf::Image tileSetImage;
                if(!tileSetImage.loadFromFile("data/tilesetmap.png"))
                    throw ImageException("tilesetmap.png"); // Throw an error if we can't
            TileProp tile;
            int numTile(0);
            string testValue;
            string line;
            string word;
            vector<string> words;
            stringstream convert;

            // Check the properties for each tile
                for(int y(0); y < m_tileSetSize.y; ++y)
                {
                    for(int x(0); x < m_tileSetSize.x; ++x)
                    {
                        if(tileSetImage.getPixel( (x*m_tileSize.x), (y*m_tileSize.y) ) !=  sf::Color(255, 0, 255))
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
                                    convert.clear();

                            // Check if the ID is good, if not: stop the game
                                if(testValue != word)
                                    throw TileException(numTile);

                            // Check each word in the line
                                while(line.length() != 0)
                                {
                                    word = line.substr(0, line.find(';'));
                                    line.erase(0, line.find(';')+1);
                                    words.push_back(word);
                                }

                            // If we don't have enough words, stop the game
                                if(words.size() < 8)
                                    throw TileException(numTile);

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

                                if(words.at(4) == "false")
                                    tile.artifact = false;
                                else
                                    tile.artifact = true;

                                if(words.at(5) == "false")
                                    tile.building = false;
                                else
                                    tile.building = true;

                                convert.str( words.at(6) );
                                convert >> tile.buildingID;
                                convert.str(string());
                                convert.clear();

                                tile.name = words.at(7);

                                convert.str( words.at(8) );
                                convert >> tile.price;
                                convert.str(string());
                                convert.clear();

                            // Put the tile in a map, so we can access it later
                                m_tilesProps[numTile] = tile;

                            // Create a tile who can't be destroy
                                if(numTile == 1)
                                {
                                    tile.diggable = false;
                                    m_tilesProps[200] = tile;
                                }

                            // Clear our variables
                                line.clear();
                                testValue.clear();
                                word.clear();
                                words.clear();
                        }

                        // Increase the number of the tile by 1 (so we don't override what we did)
                            ++numTile;
                    }
                }

            // Close the file
                tileConfig.close();
        }

        // If an exception occurred, close the file first and than rethrow it
            catch(std::exception &e)
            {
                tileConfig.close();
                throw;
            }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TilesMap::loadLevel()
{
// Initialize the random
    srand(time(NULL));

// Create the world size
    m_world.resize(29);

    ifstream worldFile("data/world.config");

    if(worldFile.is_open() && !worldFile.eof())
    {
        try
        {
            unsigned lineError(1);
            unsigned rows(0);
            unsigned rowsDone(0);
            unsigned surface(0);
            map<unsigned, unsigned> lineNumbers;
            string line;
            string subString;
            unsigned ID(0);
            unsigned number(0);
            unsigned percentage(0);
            unsigned totalPercentages(0);
            stringstream convert;

            while(!worldFile.eof())
            {
                // Get a line in the configuration file
                    getline(worldFile, line);

                // If the line start with a # or \n or is empty, get a new one
                    while(line.at(0) == '#' || line.at(0) == '\n' || line.empty())
                    {
                        line.clear();
                        getline(worldFile, line);
                        ++lineError;
                    }

                // Erase the spaces and the tabs
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

                // Find the number of rows
                    subString = line.substr(0, line.find(';'));
                    line.erase(0, line.find(';')+1);
                        convert.str( subString );
                        convert >> rows;
                        convert.str(string());
                        convert.clear();

                    surface = rows * m_world.size();

                // Check each numbers in the line
                    while(line.length() != 0)
                    {
                        subString = line.substr(0, line.find(';'));
                        line.erase(0, line.find(';')+1);

                        convert.str( subString.substr(0, subString.find('-')) );
                        convert >> ID;
                        convert.str(string());
                        convert.clear();
                        subString.erase(0, subString.find('-')+1);

                        convert.str(subString);
                        convert >> percentage;
                        convert.str(string());
                        convert.clear();

                        number = (percentage * surface / 100);

                        if( (number * 100 / surface) != percentage )
                            ++number;

                        totalPercentages += percentage;

                        lineNumbers[ID] = number;

                        //cout << ID << " : " << number << " : " << lineError << endl;;

                        ID = 0;
                        number = 0;
                        percentage = 0;
                        subString.clear();
                    }

                // Check if totalPercentages is more than 100
                    if (totalPercentages > 100)
                        throw WorldException(lineError);

                // Check if we have more tiles than the surface
                    {
                        unsigned total(0);

                        for(map<unsigned, unsigned>::iterator iter(lineNumbers.begin()); iter != lineNumbers.end(); ++iter)
                            total += iter->second;

                        if( total > surface)
                            lineNumbers.at(1) = (lineNumbers.at(1) - (total - surface));

                        if ( total < surface)
                            lineNumbers.at(1) = (lineNumbers.at(1) + (surface - total));
                    }

                 // Resize the world to fit the new tiles
                    for(unsigned i(0); i < m_world.size(); ++i )
                        m_world[i].resize(m_world[i].size() + rows);

                // Fill the world
                    {
                        unsigned randomNumber(0);
                        unsigned total(0);

                        for(unsigned x(0); x < m_world.size(); ++x)
                        {
                            for(unsigned y(rowsDone); y < m_world[0].size(); ++y)
                            {
                                randomNumber = rand()%surface;

                                for(map<unsigned, unsigned>::iterator iter(lineNumbers.begin()); iter != lineNumbers.end(); ++iter)
                                {
                                    if(randomNumber < (iter->second + total))
                                    {
                                        m_world[x][y] = iter->first;
                                        lineNumbers.at(iter->first)--;
                                        --surface;
                                        break;
                                    }

                                    else
                                        total += iter->second;
                                }

                                total = 0;
                            }
                        }
                    }

                rowsDone += rows;
                ++lineError;

                line.clear();
                rows = 0;
                surface = 0;
                ID = 0;
                number = 0;
                percentage = 0;
                totalPercentages = 0;
                subString.clear();
            }

            worldFile.close();
        }

        catch(std::exception &e)
        {
            worldFile.close();
            throw;
        }
    }

// Find the last block in y that is equal to 0 (air)
    int lastAirBlockY(0);
    for(int y = 0; y < (int)m_world[0].size(); ++y)
    {
        if(m_world[0][y] == 0)
            ++lastAirBlockY;
        else
            break;
    }

    if(lastAirBlockY != 0)
        --lastAirBlockY;

// Place the buildings
    {
        std::map<int, TileProp>::iterator first(m_tilesProps.end());
        std::map<int, TileProp>::iterator last(m_tilesProps.end());
        unsigned space(5);
        unsigned x = space;
        unsigned counter(0);
        unsigned positionX(1);

        for(m_iter = m_tilesProps.begin(); m_iter != m_tilesProps.end(); ++m_iter)
        {
            // If it's a building and we did not initialize the first iterator (it's the beginning of a building)
                if(m_iter->second.building && first == m_tilesProps.end())
                    first = m_iter;
            // If it's not the same buildingID (so not the same building), set the iterator last (it's one pas the end of the building)
                if(m_iter->second.buildingID != first->second.buildingID && first != m_tilesProps.end())
                    last = m_iter;
            // If we have the beginning and the end of the building
                if(last != m_tilesProps.end() && first != m_tilesProps.end())
                {
                    for( ; first != last; ++first)
                    {
                        // Find the position in the name of the building
                            positionX = first->second.name.find_first_of("0123456789");
                            if(positionX != string::npos)
                                positionX = first->second.name.at(positionX) - '0';

                        // If we find Top in the name of the building
                            if(first->second.name.find("Top") != string::npos)
                                m_world[ (x + positionX - 1) ][ (lastAirBlockY - 1) ] = first->first;

                        // If we find Down in the name of the building
                            if(first->second.name.find("Down") != string::npos)
                            {
                                m_world[ (x + positionX - 1) ][ lastAirBlockY ] = first->first;
                                m_world[ (x + positionX - 1) ][ lastAirBlockY + 1] = 200;
                            }

                        // So we have highest position in x
                            if(positionX > counter)
                                counter = positionX;
                    }

                    // Add some space so the next building will not be drawn at the same place
                        x += (space + counter);

                    // If the last iterator point on a building, it's now our first iterator
                        if(last->second.building)
                            first = last;
                        else // Else, reset the iterator
                            first = m_tilesProps.end();

                    // Reset the last operator
                        last = m_tilesProps.end();
                }
        }
    }

// Define the vector world size
    m_worldSize.x = (int)m_world.size() * m_tileSize.x;
    m_worldSize.y = (int)m_world[0].size() * m_tileSize.y;
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

int TilesMap::getTile(int x, int y)
{
    return m_world[x][y];
}
