#include "prop.h"

Prop::Prop()
{
    this->tipo = pNone;
    setPrinted(false);
}

Prop::Prop(TypoP tipo, sf::Texture* texturas, int size) {
    this->tipo = tipo;
    this->setTexture(*texturas);
    setPrinted(false);
}

