#include "util.h"
#include <iostream>


sf::Vector2f dirToVec(Direction dir) {
    sf::Vector2f vec;
    switch (dir) {
    case Up:
        vec = sf::Vector2f(-1,0);
        break;
    case Down:
        vec = sf::Vector2f(1,0);
        break;
    case Right:
        vec = sf::Vector2f(0,1);
        break;
    case Left:
        vec = sf::Vector2f(0,-1);
        break;
    default:
        break;
    }
    return vec;
}

sf::Vector2f dirNormaliced(sf::Vector2f v) {
    if (v.x == -1) v.x = 0;
    if (v.y == -1) v.y = 0;
    return v;
}

sf::Vector2i vecfToVeci(sf::Vector2f vc) {
    sf::Vector2i aux;
    aux.x = int(vc.x);
    aux.y = int(vc.y);
    return aux;
}

bool changingNumber(float antes, float despues) {
    return (int(despues)-int(antes) != 0);
}

sf::Vector2f vecfTrunc(sf::Vector2f vec) {
    vec.x = int(vec.x);
    vec.y = int(vec.y);
    return vec;
}
