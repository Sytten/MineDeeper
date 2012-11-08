#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
    public:
    Map(int NbrTilesWidth, int NbrTilesHeight);
    void create();
    //void setTile(int x, int y);

    private:

    sf::Texture sky;
    sf::Texture land;

    int m_nbrTilesWidth;
    int m_nbrTilesHeight;
    std::vector<int> table;

    friend void draw(sf::RenderWindow &window, const Map *map);
};


#endif
