#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

extern int WIDTH;
extern int HEIGHT;

extern int ROWS;
extern int COLS;

extern const int TILE_SIZE;
extern const float UISPACE;

extern bool GENERATE_MAP;

enum Land { //Terrain
    None, Rock, Grass, Water
};

#define NPROPS 2
enum Resource {
    Star, BStar, Stone, Tree, Fish
};

enum Direction {
    Up, Right, Down, Left
};

struct Way {
    Direction dir;
    int dist;
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
std::string resourceToString (Resource r);

sf::Color getColor(int n);

#endif // UTIL_H
