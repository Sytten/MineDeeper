#ifndef MAP_H
#define MAP_H

#include <map>

#include <SFML/Graphics.hpp>

#include "Collisions.h"

class TilesMap
{
    private:
        void loadTileSet();
        void loadLevel();

        int m_tileWidth; //the map specifications
        int m_tileHeight;
        int m_worldWidth;
        int m_worldHeight;

        std::vector<int> table; //our world

        struct TileProp
        {
            public:
            sf::Rect<int> tileRect;
            bool full;
        };

        sf::Texture m_tileSet;
        int m_nbrTilesX; //number of tiles in the tileset
        int m_nbrTilesY;
        std::map<int, TileProp> m_tilesProps; //to keep our TileProp

        friend void draw(sf::RenderWindow &window, const TilesMap &tilesMap);
        friend class Collisions;


    public:
        TilesMap();
        void create();
        TileProp getTileProp(int tile) const;
};


#endif
