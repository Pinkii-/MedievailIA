#include "prop.h"

Prop::Prop()
{
    this->tipo = pNone;
    setPrinted(false);
}

Prop::Prop(TypoP tipo, sf::Texture* texturas, sf::Vector2f pos, int size) {
    this->tipo = tipo;
    posMatrix = pos;
    this->setTexture(*texturas);
    setPrinted(false);

    float scalex, scaley;
    scalex =  size/float(texturas->getSize().x);
    scaley =  size/float(texturas->getSize().y);

    this->setScale(scalex,scaley);
}

void Prop::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

sf::Vector2f Prop::getMatPosition() {
    return posMatrix;
}
