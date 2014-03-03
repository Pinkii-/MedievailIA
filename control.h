#ifndef CONTROL_H
#define CONTROL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "npc.h"
#include "prop.h"
#include "player.h"

class Control : public sf::Drawable
{
private:
    Map* m;
    std::vector<Player> players;
    std::vector<std::vector<Prop> > props;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Control();
    void init(Map *map);
    void update(float deltaTime, Map &m);
    void updateProp(float deltaTime, Map &m);
    void updateDraw(sf::Vector2f cameraPos);
    void erasePropN(std::vector<Prop> &v,int n);
    std::vector<sf::Vector2f> getObjetiveNpc(Resource preference);
    Npc getNpc(int player, int i);
    bool npcOnProp(int j);
};

#endif // CONTROL_H
