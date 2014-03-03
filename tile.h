#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "util.h"


class Tile : public sf::Sprite
{
private:
    sf::Texture *pTextura;
    bool printed;
public:
    Tile();
    Tile(sf::Texture *texturas);
    virtual Land getLand();
    bool isPrinted() const; //Just dont
    void setPrinted(bool b);
};

#endif // TILE_H
