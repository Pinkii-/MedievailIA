#ifndef NPC_H
#define NPC_H

#include "tile.h"

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

class Npc : public Tile
{
private:
    sf::Vector2f posMatrix;
    sf::Vector2f speed;
    HitBox box;
public:
    Npc();
    Npc(sf::Texture* texturas,sf::Vector2f pos, int size, HitBox h);

    void setMatPosition(sf::Vector2f pos);

    sf::Vector2f getMatPosition();
    sf::Vector2f getSpeed();
    HitBox getHitBox();
};

#endif // NPC_H
