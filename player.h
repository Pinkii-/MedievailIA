#ifndef PLAYER_H
#define PLAYER_H

#include "vector"

#include "npc.h"
#include "Building.h"
#include "map.h"

class Control;
class Player : public sf::Drawable
{
private:
    Control* c;
    Map* m;
    std::vector<Npc> npcs;
    std::vector<Building> buildings;
    sf::Color color;
    // Class? Race?
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Player();

    void init(int nColor,Control* con, Map* map);
    void buildingInit();
    void npcInit();

    void updateDraw(sf::Vector2f cameraPos);
    void update(float deltaTime);
    void updateNpcs(float deltaTime);

    std::vector<Npc> getNpcs();
};

#endif // PLAYER_H
