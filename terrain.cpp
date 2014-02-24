#include "terrain.h"

Terrain::Terrain()
{
}

Terrain::Terrain(Typo tipo, int size) {
    this->tipo = tipo;
	switch (tipo) {
		case None:
			this->setTexture(Textures::none);
			break;
		case Rock:
			this->setTexture(Textures::rock);
			break;
		default:
			break;
	}


    setPrinted(false);


    float scalex, scaley;
	scalex =  size/float(this->getTexture()->getSize().x);
	scaley =  size/float(this->getTexture()->getSize().y);

    this->setScale(scalex,scaley);
}

Typo Terrain::getTypo() {
    return this->tipo;
}
