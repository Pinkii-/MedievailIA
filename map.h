#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "terrain.h"
#include "prop.h"

class Map : public sf::Drawable
{
private:
    std::vector<std::vector<Terrain> > matrix;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Map();
	Map(int cols, int rows);
    void generateMap();
    void generateProps();
    void loadMap();
    void update(float deltaTime);
    void updateDraw(sf::Vector2f cameraPos);
    bool isWalkeable(sf::Vector2f pos);

};

#endif // MAP_H
