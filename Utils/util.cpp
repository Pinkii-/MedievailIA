#include "util.h"
#include <iostream>
#include <stdio.h>
#include <math.h>



sf::Vector2f dirToVec(Direction dir) {
    sf::Vector2f vec;
    switch (dir) {
    case Up:
        vec = sf::Vector2f(0,-1);
        break;
    case Down:
        vec = sf::Vector2f(0,1);
        break;
    case Right:
        vec = sf::Vector2f(1,0);
        break;
    case Left:
        vec = sf::Vector2f(-1,0);
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
    aux.x = int(round(vc.x));
    aux.y = int(round(vc.y));
    return aux;
}

sf::Vector2f absoluteValue(sf::Vector2f v) {
    v.x = int(v.x);
    v.y = int(v.y);
    return v;
}

bool changingNumber(float antes, float despues) {
    return (int(despues)-int(antes) != 0);
}

sf::Vector2f vecfTrunc(sf::Vector2f vec) {
    
    vec.x = int(vec.x);
    vec.y = int(vec.y);
    
    return vec;
}

sf::Vector2f operator + (sf::Vector2f vec, Direction d) {
    switch (d) {
    case Up:
        --  vec.y;
        break;
    case Down:
        ++vec.y;
        break;
    case Right:
        ++vec.x;
        break;
    case Left:
        --vec.x;
        break;
    default:
        break;
    }
    return vec;
}

sf::Vector2f operator - (sf::Vector2f vec, Direction d) {
    switch (d) {
    case Up:
        ++vec.y;
        break;
    case Down:
        --vec.y;
        break;
    case Right:
        --vec.x;
        break;
    case Left:
        ++vec.x;
        break;
    default:
        break;
    }
    return vec;
}

Direction opposite(Direction d) {
    Direction dd;
    switch (d) {
    case Up:
        dd = Down;
        break;
    case Down:
        dd = Up;
        break;
    case Right:
        dd = Left;
        break;
    case Left:
        dd = Right;
        break;
    default:
        break;
	}
	return dd;
}

std::string resourceToString (Resource r)
{
    std::string s;
    switch (r){
    case Star:
        s = "Yellow Star";
        break;
    case BStar:
        s = "Black Star";
        break;
    default:
        s = "Not a Resource";
    }

    return s;
}

sf::Color getColor(int n) {
	float ratio = 50;
	int r = ratio * n;
	int g = ratio * (r/256);
	int b = ratio * (g/256);

	r %= 256;
	g %= 256;
	b %= 256;

	return sf::Color(r,g,b);
}
