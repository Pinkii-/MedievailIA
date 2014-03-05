#include "tile.h"
#include <iostream>

Tile::Tile()
{
}

Tile::Tile(sf::Texture* texturas) {
    this->setTexture(*texturas);
    printed = false;
}

void Tile::setPrinted(bool b) {
    printed = b;
}

Land Tile::getLand() { // El polimorfismo esta broken
    Land aux = None;
    return aux;
}

bool Tile::isPrinted() const {
    return printed;
}

//this->setOrigin(50,50);
//    sf::IntRect wola;
//    wola.contains(size,size);
//    this->setTextureRect(wola);
