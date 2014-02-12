#ifndef NPC_H
#define NPC_H

#include "tile.h"
#include "util.h"
#include "terrain.h"
#include "map.h"

#include <queue>
#include <stack>
#include <list>


class Npc : public Tile
{
private:
    sf::Vector2f posMatrix;
    std::vector<sf::Vector2f> posDestino;
    float speed;

    bool waiting;
    std::queue<Direction> way;
    Direction dir;
    std::list<TypoP> preferences;

    float waitTime;


public:
    Npc();
    Npc(sf::Texture* texturas, sf::Vector2f pos, int size);

    void initPreferences();
    void setPreference(TypoP p);
    TypoP getPreference();

    void setMatPosition(sf::Vector2f pos);
    void setDesPosition(std::vector<sf::Vector2f> pos);

    sf::Vector2f getMatPosition();
    float getSpeed();

    void decrementSpeed();
    void setWaitTime(float deltaTime);

    void update(float delta, Map &m);
    bool checkWay(Map &m);
    void calculateWay(Map &m);
    bool isOnDest(sf::Vector2i n);


};

#endif // NPC_H
