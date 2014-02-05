#include "terrain.h"

Terrain::Terrain()
{
}

Terrain::Terrain(Typo tipo, sf::Texture* texturas, int size) {
    this->tipo = tipo;
    this->setTexture(*texturas);
    setPrinted(false);
}

Typo Terrain::getTypo() {
    return this->tipo;
}
