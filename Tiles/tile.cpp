#include "tile.h"
#include <iostream>

Tile::Tile()
{
}

Tile::Tile(sf::Texture* texturas) {
    this->setTexture(*texturas);
    printed = false;
}

Land Tile::getLand() { // El polimorfismo esta broken
    Land aux = None;
    return aux;
}


//this->setOrigin(50,50);
//    sf::IntRect wola;
//    wola.contains(size,size);
//    this->setTextureRect(wola);
