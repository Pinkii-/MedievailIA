#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"
#include "util.h"
#include "Textures.hpp"

class Terrain : public Tile
{
private:
    Typo tipo;

public:
    Terrain();
	Terrain(Typo tipo, int size);

    Typo getTypo() override; //Override mis cojones
};

#endif // TERRAIN_H
