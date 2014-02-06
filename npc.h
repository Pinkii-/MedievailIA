#ifndef NPC_H
#define NPC_H

#include "tile.h"
#include "util.h"

#include "terrain.h"
#include "map.h"
#include <stack>

class Npc : public Tile
{
private:
    sf::Vector2f posMatrix;
    float speed;
    HitBox box;
    std::stack<Direction> way;

    bool waiting;
    sf::Vector2i posDestino;
    Direction dir;

public:
    Npc();
    Npc(sf::Texture* texturas, sf::Vector2f pos, int size);

    void setMatPosition(sf::Vector2f pos);

    sf::Vector2f getMatPosition();
    float getSpeed();
    HitBox getHitBox();


    void update(float delta, Map &m);
    bool checkWay(Map &m);
    void calculateWay(sf::Vector2i destino, Map &m);

};

#endif // NPC_H
