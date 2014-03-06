#include "Building.h"

Building::Building()
{
}



void Building::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

sf::Vector2f Building::getMatPosition() {
    return posMatrix;
}
