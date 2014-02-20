#ifndef CONTROL_H
#define CONTROL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "npc.h"
#include "prop.h"

class Control : public sf::Drawable
{
private:
     std::vector<Npc> npcs;
     std::vector<std::vector<Prop> > props;
     std::vector<sf::Texture> texturas;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Control();
    Control(std::vector<sf::Texture> *text);
    void npcInit();
    void update(float deltaTime, Map &m);
    void updateProp(float deltaTime, Map &m);
    void updatePosNpc(float deltaTime, Map &m);
    void updateObjetiveNpc();
	std::vector<sf::Vector2f> getObjetiveNpc(TypoP preference);
    void updateDraw(sf::Vector2f cameraPos);

    Npc getNpc(int i);
    bool npcOnProp(float deltaTime, int j);
    void erasePropN(std::vector<Prop> &v,int n);
};

#endif // CONTROL_H
