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
    sf::Vector2f speed;
    HitBox box;

    bool waiting;
    Direction dir;
public:
    Npc();
    Npc(sf::Texture* texturas, sf::Vector2f pos, int size, HitBox h);

    void setMatPosition(sf::Vector2f pos);

    sf::Vector2f getMatPosition();
    sf::Vector2f getSpeed();
    HitBox getHitBox();

    //void update(Map<Terrain> &m);
};

#endif // NPC_H
