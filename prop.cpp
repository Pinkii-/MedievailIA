#include "prop.h"

Prop::Prop()
{
}

Prop::Prop(Resource tipo, sf::Vector2f pos, int size) {
    this->tipo = tipo;
    posMatrix = pos;
    setPrinted(false);

	this->setTexture(Textures::star);


    float scalex, scaley;
	scalex =  size/float(this->getTexture()->getSize().x);
	scaley =  size/float(this->getTexture()->getSize().y);

    this->setScale(scalex,scaley);

    if (tipo == BStar) this->setColor(sf::Color::Black);
}

void Prop::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

sf::Vector2f Prop::getMatPosition() {
    return posMatrix;
}

Resource Prop::getResource() {
    return tipo;
}
