#ifndef MAP_H
#define MAP_H

#include <map>

#include <SFML/Graphics.hpp>

#include "Collisions.h"

class Camera;

class TilesMap
{
    private:
        void loadTileSet();
        void loadLevel();

        sf::Vector2i m_tileSize;
        sf::Vector2i m_worldSize;
        std::vector<std::vector<int> > m_world; //our world

        struct TileProp
        {
            public:
            sf::Rect<int> posInTileSet;
            bool walkable;
        };

        sf::Texture m_tileSet;
        sf::Vector2i m_tileSetSize;
        std::map<int, TileProp> m_tilesProps; //to keep our TileProp

        //to draw
        sf::Sprite m_tile;
        sf::Vector2<int> m_camOffSet;
        sf::Rect<int> m_bounds;

    public:
        TilesMap(int tileSizeX, int tileSizeY);
        void create();
        TileProp getTileProp(int tile) const;
        sf::Vector2i getWorldSize() const { return m_worldSize; }
        sf::Vector2i getTileSize() const { return m_tileSize; }
        void setTile(int x, int y, int blockID);


        friend void draw(sf::RenderWindow &window, TilesMap &tilesMap, const Camera &camera);
        friend class Collisions;
};


#endif
