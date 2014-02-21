#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

extern int WIDTH;
extern int HEIGHT;

extern int ROWS;
extern int COLS;

extern int TILE_SIZE;

extern bool GENERATE_MAP;

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

Direction opposite(Direction d);

sf::Color getColor(int n);

#endif // UTIL_H
