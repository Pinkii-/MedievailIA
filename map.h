#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
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
    bool isWalkeable(sf::Vector2f pos);

    void update(float deltaTime);
	sf::Vector2f updateCamera(float deltaTime, sf::Vector2f dir, sf::Vector2f cameraPos, float cameraVel);
    void updateDraw(sf::Vector2f cameraPos);
};

#endif // MAP_H
