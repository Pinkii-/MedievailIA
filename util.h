#ifndef UTIL_H
#define UTIL_H

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

//struct Way {
//    Direction d;
//    int distancia;
//};

struct HitBox {
    int minX, maxX, minY, maxY;
};

enum texturas {
    tNone, tRock, tNpc
};


#endif // UTIL_H
