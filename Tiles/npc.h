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

    std::vector<sf::Vector2f> posDestino;
    std::queue<Direction> way;
    std::list<Resource> preferences;
    
    Direction dir;
    Resource goingTo;
    sf::Vector2f posMatrix;

    int maxRange;
    float speed;
    float waitTime;
    bool waiting;
public:
    // Constructors
    Npc();
    Npc(sf::Vector2f pos, int size, Control *con, Map *map);

    // Inits
    void initPreferences();

    // Updaters
    void update(float delta);
    void calculateWay();
    bool checkWay(Map &m);

    // Setters
    void setMatPosition(sf::Vector2f pos);
    void setDesPosition(std::vector<sf::Vector2f> pos);
    void setMaxRange(int pasos);
    void decrementSpeed();
    void setWaitTime(float deltaTime);
    void setPreference(Resource p);
    
    // Getters
    Resource getPreference();
    sf::Vector2f getMatPosition();
    bool isOnDest(sf::Vector2i n);
    float getSpeed();
};

#endif // NPC_H
