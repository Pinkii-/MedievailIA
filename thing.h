#ifndef OBJECT_H
#define OBJECT_H

#include "tile.h"
#include "util.h"

class Thing : public Tile
{
private:
    TypoO tipo;
public:
    Thing();
    Thing(TypoO tipo, sf::Texture* texturas, int size);
};

#endif // OBJECT_H
