#ifndef BASE_HPP
#define BASE_HPP
#include "Tiles/Building.h"

class Base : public Building
{
public:
	Base(sf::Vector2f pos, int size);
	void update(float deltaTime);
};

#endif // BASE_HPP
