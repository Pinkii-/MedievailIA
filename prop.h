#ifndef PROP_H
#define PROP_H

#include "tile.h"
#include "util.h"

class Prop : public Tile
{
private:
    TypoO tipo;
public:
    Prop();
    Prop(TypoO tipo, sf::Texture* texturas, int size);
};

#endif // PROP_H
