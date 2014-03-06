#include "Interface.hpp"
#include "board.h"
#include "Utils/util.h"

void Interface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(fondo);
    for (unsigned int i = 0; i < n.size(); ++i) target.draw(n[i]);
}

Interface::Interface() {
}

void Interface::init(Board *g) {
	game = g;
	fondo = sf::RectangleShape(sf::Vector2f(TILE_SIZE*UISPACE,HEIGHT));
	fondo.setPosition(0,0);
	fondo.setFillColor(sf::Color(200,200,200));
    n = std::vector<NpcDisplayer>(g->getControl().getPlayer().getNpcs().size());
    for (unsigned int i = 0; i < n.size(); ++i) n[i] = NpcDisplayer(i,g->getControl().getPlayer().getNpcs()[i]);
}

void Interface::update() {

}

