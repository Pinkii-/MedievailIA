#ifndef NPC_H
#define NPC_H

#include <queue>
#include <stack>
#include <list>

#include "Tiles/tile.h"
#include "Utils/util.h"
#include "Tiles/terrain.h"
#include "map.h"
#include "Utils/Textures.hpp"



class Control;
class Npc : public Tile
{
private:
    Control* c;
    Map* m;

	std::vector<sf::Vector2f> vTargetDestinations;
    sf::Vector2f TargetDestination;

    std::queue<Direction> way;
    std::list<Resource> preferences;
	
    Direction dir;
    Resource goingTo;
    sf::Vector2f posMatrix;
    float speed;
    float waitTime;
    bool waiting;
    int maxDistance;

    npcState state;
    int amount;

public:
    Npc();
    Npc(sf::Vector2f pos, int size, Control *con, Map *map);
    void initPreferences();
    void update(float delta);
    void setMatPosition(sf::Vector2f pos);
    void setDesPosition(std::vector<sf::Vector2f> pos);
    void decrementSpeed();
    void setWaitTime(float deltaTime);
    void calculateWay();
    void setPreference(Resource p);
    void setMaxDistance(int dist);
	void resetWay();
    Resource getPreference();
    sf::Vector2f getMatPosition();
	sf::Vector2f getTargetDestination();
    int getMaxDistance();
    Map* getMap();
    bool isOnDest(sf::Vector2i n);
    bool checkWay(Map &m);
    float getSpeed();
};

#endif // NPC_H
