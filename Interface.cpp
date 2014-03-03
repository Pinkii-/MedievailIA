#include "Interface.hpp"
#include "board.h"
#include "util.h"

void Interface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(fondo);
}

Interface::Interface() {
}

void Interface::init(Board *g) {
	game = g;
	fondo = sf::RectangleShape(sf::Vector2f(TILE_SIZE*UISPACE,HEIGHT));
	fondo.setPosition(0,0);
	fondo.setFillColor(sf::Color(200,200,200));
}

void Interface::update() {

}

