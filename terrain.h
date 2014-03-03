#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"
#include "util.h"
#include "Textures.hpp"

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
