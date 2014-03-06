#ifndef BUILDING_H
#define BUILDING_H

#include "tile.h"

class Building : public Tile
{
private:
    sf::Vector2f posMatrix;
public:
    Building();
    virtual void update(float deltaTime) = 0;
    void setMatPosition(sf::Vector2f pos);
    sf::Vector2f getMatPosition();
};

#endif // BUILDING_H
