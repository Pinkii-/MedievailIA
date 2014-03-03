#ifndef PLAYER_H
#define PLAYER_H

#include "vector"

#include "control.h"
#include "npc.h"
#include "Building.h"

class Control;
class Player
{
private:
    Control* c;
    std::vector<Npc> npcs;
    std::vector<Building> buildings;
    sf::Color color;
    // Class? Race?
public:
    Player();
    Player(int nColor,Control* con);
};

#endif // PLAYER_H
