#ifndef NPCDISPLAYER_HPP
#define NPCDISPLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Tiles/npc.h"

#define nTextosNpcDisplayer 2

class NpcDisplayer : public sf::Drawable {
private:
    Npc* n;
    sf::RectangleShape s;
    int height, width;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<sf::Text> texts;
public:
    NpcDisplayer();
    NpcDisplayer(int position,Npc* npc);
    void update();
    bool isClicked(sf::Vector2f pos);
    Npc* getNpc();
};

#endif // NPCDISPLAYER_HPP
