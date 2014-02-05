#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>

#define WIDTH 1000
#define HEIGHT 500

#define ROWS 30
#define COLS 30

#define TILE_SIZE 40

#define NTEXTURES 3

enum Typo { //Terrain
    None, Rock, Wood
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

enum texturas {
    tNone, tRock, tNpc
};

sf::Vector2f dirToVec(Direction dir);

sf::Vector2f dirNormaliced (sf::Vector2f dir);

sf::Vector2i vecfToVeci(sf::Vector2f vc);

bool changingNumber(float antes, float despues);

sf::Vector2f vecfTrunc(sf::Vector2f vec);

#endif // UTIL_H
