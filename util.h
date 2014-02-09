#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>

#define WIDTH 1000
#define HEIGHT 500

#define ROWS 30
#define COLS 30

#define TILE_SIZE 40



enum Typo { //Terrain
    None, Rock, Wood
};

#define NPROPS 2
enum TypoP {
    Star, BStar
};

#define NTEXTURES 4
enum texturas {
    tNone, tRock, tNpc, tStar
};

enum Direction {
    Up, Right, Down, Left
};

struct Way {
    Direction d;
    int distancia;
};

struct HitBox {
    int minX, maxX, minY, maxY;
};

sf::Vector2f dirToVec(Direction dir);

sf::Vector2f dirNormaliced (sf::Vector2f dir);

sf::Vector2i vecfToVeci(sf::Vector2f vc);
sf::Vector2f absoluteValue(sf::Vector2f v);

bool changingNumber(float antes, float despues);

sf::Vector2f vecfTrunc(sf::Vector2f vec);

sf::Vector2f operator + (sf::Vector2f vec, Direction d);
sf::Vector2f operator - (sf::Vector2f vec, Direction d);

#endif // UTIL_H
