#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>



class Tile : public sf::Sprite
{
private:
    sf::Texture *pTextura;
    bool printed;
public:
    Tile();
    Tile(sf::Texture *texturas);
    bool isPrinted() const;
    void setPrinted(bool b);
};

#endif // TILE_H
