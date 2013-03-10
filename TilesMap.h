// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TilesMap.h
// The header file of the TilesMap object. See the cpp file for more
// information about the class.
//
// Author: Sytten
// Creation date: 05/11/2012
// Last modification date: 05/03/2013
// ---------------------------------------------------------------------------

#ifndef TILESMAP_H
#define TILESMAP_H

#include <map>

#include <SFML/Graphics.hpp>

#include "Collisions.h"

class Camera;

class TilesMap
{
    private:
        struct TileProp
        {
            public:
            sf::Rect<int> posInTileSet;
            bool walkable;
            bool diggable;
            bool ore;
            bool door;
            bool building;
                unsigned buildingID;
            bool artifact;
            std::string name;
            int price;
        };

    public:
        TilesMap(int tileSizeX, int tileSizeY);
        TileProp getTileProp(int tile) const;
        sf::Vector2i getWorldSize() const { return m_worldSize; }
        sf::Vector2i getTileSize() const { return m_tileSize; }
        void setTile(int x, int y, int blockID);
        int getTile(int x, int y);

    private:
        void loadTileSet();
        void loadLevel();

        // World related variables
            sf::Vector2i m_tileSize;
            sf::Vector2i m_worldSize;
            std::vector<std::vector<int> > m_world; // Our world

        // TileSet related variables
            sf::Texture m_tileSet;
            sf::Vector2i m_tileSetSize;
            std::map<int, TileProp> m_tilesProps; // To keep our TileProp
            std::map<int, TileProp>::iterator m_iter;

        // To draw
            sf::Sprite m_tile;
            sf::Vector2<int> m_camOffSet;
            sf::Rect<int> m_bounds;



        friend void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera);
        friend class Collisions;
};

#endif
