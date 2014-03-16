#ifndef PLAYER_H
#define PLAYER_H

#include "vector"

#include "Tiles/npc.h"
#include "Tiles/Building.h"
#include "Tiles/Buildings/Base.hpp"
#include "map.h"

class Control;
class Player : public sf::Drawable
{
private:
    Control* c;
    Map* m;
    std::vector<Npc*> npcs;
    std::vector<Building*> buildings;
    sf::Color color;
    // Class? Race?
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Player();
    void init(int nColor,Control* con, Map* map);
    void buildingInit();
    void npcInit();
    void update(float deltaTime);
    void updateNpcs(float deltaTime);
    void updateBuildings(float deltaTime);
    void updateDraw(sf::Vector2f cameraPos);
	void addNpc();
    std::vector<Npc*> getNpcs();
    std::vector<sf::Vector2f> getBase();
};

#endif // PLAYER_H
