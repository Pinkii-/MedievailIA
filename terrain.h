#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"
#include "util.h"

class Terrain : public Tile
{
private:
    Typo tipo;

public:
    Terrain();
    Terrain(Typo tipo, sf::Texture* texturas, int size);

    Typo getTypo();
};

#endif // TERRAIN_H
