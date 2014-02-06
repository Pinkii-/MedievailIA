#include "prop.h"

Prop::Prop()
{
}

Prop::Prop(TypoO tipo, sf::Texture* texturas, int size) {
    this->tipo = tipo;
    this->setTexture(*texturas);
    setPrinted(false);
}

