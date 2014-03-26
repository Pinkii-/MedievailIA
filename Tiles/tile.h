#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "Utils/util.h"


class Tile : public sf::Sprite
{
private:
    sf::Texture *pTextura;
    bool printed;
public:
    Tile();
    Tile(sf::Texture *texturas);
    virtual Land getLand();

};

#endif // TILE_H
