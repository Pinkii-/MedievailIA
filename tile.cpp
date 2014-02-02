#include "tile.h"

Tile::Tile()
{
}

Tile::Tile(sf::Texture* texturas) {
    this->setTexture(*texturas);
    printed = false;
}

bool Tile::isPrinted() const {
    return printed;
}

void Tile::setPrinted(bool b) {
    printed = b;
}


//this->setOrigin(50,50);
//    sf::IntRect wola;
//    wola.contains(size,size);
//    this->setTextureRect(wola);
