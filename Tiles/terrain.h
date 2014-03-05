#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"
#include "Utils/util.h"
#include "Utils/Textures.hpp"

class Terrain : public Tile
{
private:
    Land tipo;
public:
    Terrain();
    Terrain(Land tipo, int size);
    Land getLand(); //Override mis cojones
};

#endif // TERRAIN_H
