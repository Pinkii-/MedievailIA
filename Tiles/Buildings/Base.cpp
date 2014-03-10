#include "Base.hpp"
#include "Utils/Textures.hpp"

Base::Base(sf::Vector2f pos, int size) {
	this->setTexture(Textures::BuildingBase);
	this->setColor(sf::Color::Red);

	posMatrix = pos;

	float scalex, scaley;
	scalex =  size/float(this->getTexture()->getSize().x);
	scaley =  size/float(this->getTexture()->getSize().y);

	this->setScale(scalex,scaley);
}

void Base::update(float deltaTime){

}
