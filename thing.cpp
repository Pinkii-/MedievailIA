#include "thing.h"

Thing::Thing()
{
}

Thing::Thing(TypoO tipo, sf::Texture* texturas, int size) {
    this->tipo = tipo;
    this->setTexture(*texturas);
    setPrinted(false);
}

