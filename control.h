#ifndef CONTROL_H
#define CONTROL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tiles/npc.h"
#include "Tiles/prop.h"
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
    void updateProp(Map &m);
    void initDraw();
    void erasePropN(std::vector<Prop> &v,int n);
	void forceToUpdateObjective(sf::Vector2f pos);
    std::vector<sf::Vector2f> getObjetiveNpc(Resource preference);
    Npc getNpc(int player, int i);
    Player getPlayer();
    bool npcOnProp(int j);
};

#endif // CONTROL_H
