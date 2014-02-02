#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"

enum Typo {
    None, Rock, Wood
};


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
