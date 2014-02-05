#ifndef NPC_H
#define NPC_H

#include "tile.h"
#include "util.h"

#include "terrain.h"
#include "map.h"

class Npc : public Tile
{
private:
    sf::Vector2f posMatrix;
    float speed;
    HitBox box;

    bool waiting;
    sf::Vector2i posDestino;
    Direction dir;
public:
    Npc();
    Npc(sf::Texture* texturas, sf::Vector2f pos, int size, HitBox h);

    void setMatPosition(sf::Vector2f pos);

    sf::Vector2f getMatPosition();
    float getSpeed();
    HitBox getHitBox();


    void update(float delta, Map &m);
};

#endif // NPC_H
