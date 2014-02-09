#ifndef PROP_H
#define PROP_H

#include "tile.h"
#include "util.h"

class Prop : public Tile
{
private:
    sf::Vector2f posMatrix;
    TypoP tipo;
public:
    Prop();
    Prop(TypoP tipo, sf::Texture* texturas, sf::Vector2f pos, int size);

    void setMatPosition(sf::Vector2f pos);
    sf::Vector2f getMatPosition();
    TypoP getTypoP();
};

#endif // PROP_H
