#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Utils/Textures.hpp"
#include "Npcdisplayer.hpp"

class Board;
class Interface : public sf::Drawable {
private:
    std::vector<Terrain> mask;
    std::vector<NpcDisplayer> n;
    Board* game;
    sf::RectangleShape fondo;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Interface();
    void init(Board* g);
    void update();
    void setMask(Npc* n);
};

#endif // INTERFACE_HPP
