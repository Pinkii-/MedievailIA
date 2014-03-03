#ifndef PROP_H
#define PROP_H

#include "tile.h"
#include "util.h"
#include "Textures.hpp"

class Prop : public Tile
{
private:
    sf::Vector2f posMatrix;
    Resource tipo;
public:
    Prop();
    Prop(Resource tipo, sf::Vector2f pos, int size);

    void setMatPosition(sf::Vector2f pos);
    sf::Vector2f getMatPosition();
    Resource getResource();
};

#endif // PROP_H
