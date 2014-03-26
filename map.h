#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tiles/terrain.h"
#include "Tiles/prop.h"

class Map : public sf::Drawable
{
private:
    std::vector<std::vector<Terrain> > matrix;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Map();
	Map(int cols, int rows);
    void generateMap();
    void loadMap();
    void initDraw();
    bool isWalkeable(sf::Vector2f pos);
    sf::Vector2i getSize();
    Terrain getTerrain(int x, int y);

};

#endif // MAP_H
