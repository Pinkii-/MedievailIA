#include "terrain.h"

Terrain::Terrain()
{
}

Terrain::Terrain(Typo tipo, sf::Texture* texturas, int size) {
    this->tipo = tipo;
    this->setTexture(*texturas);
    setPrinted(false);


//    float scalex, scaley;
//    scalex =  size/float(texturas->getSize().x);
//    scaley =  size/float(texturas->getSize().y);

//    this->setScale(scalex,scaley);
}

Typo Terrain::getTypo() {
    return this->tipo;
}
