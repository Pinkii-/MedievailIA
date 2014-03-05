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
    void setPrinted(bool b);
    virtual Land getLand();
    bool isPrinted() const; //Just dont

};

#endif // TILE_H
