#include "Interface.hpp"
#include "board.h"
#include "Utils/util.h"

#include <stdio.h>

void Interface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < mask.size(); ++i) target.draw(mask[i]);
    target.draw(fondo);
    for (unsigned int i = 0; i < n.size(); ++i) target.draw(n[i]);
}

Interface::Interface() {
}

void Interface::init(Board *g) {
	game = g;
    mask = std::vector<Terrain>();
	fondo = sf::RectangleShape(sf::Vector2f(TILE_SIZE*UISPACE,HEIGHT));
	fondo.setPosition(0,0);
	fondo.setFillColor(sf::Color(200,200,200));
    n = std::vector<NpcDisplayer>(g->getControl().getPlayer().getNpcs().size());
    for (unsigned int i = 0; i < n.size(); ++i) n[i] = NpcDisplayer(i,g->getControl().getPlayer().getNpcs()[i]);
}

void Interface::update() {
    for (unsigned int i = n.size(); i < game->getControl().getPlayer().getNpcs().size(); ++i) n.push_back(NpcDisplayer(i,game->getControl().getPlayer().getNpcs()[i]));
    for (unsigned int i = 0; i < n.size();++i) n[i].update();
    setMask(n[0].getNpc()); //provisonal to test setMask();
}

void Interface::setMask(Npc* n) {
    mask = std::vector<Terrain>();
    sf::Vector2f pos = n->getMatPosition() ;
    std::vector<std::vector<bool> > visitado(COLS, std::vector<bool>(ROWS,false));
    std::vector<std::vector<int> > camino(COLS, std::vector<int>(ROWS));
    std::queue<sf::Vector2i> sinVisitar;
    visitado[int(pos.x)][int(pos.y)] = true;
    camino[int(pos.x)][int(pos.y)] = 0;
    sinVisitar.push(vecfToVeci(pos));
    while (!sinVisitar.empty()) {
        sf::Vector2i visitando = sinVisitar.front();
        sinVisitar.pop();
        if(camino[visitando.x][visitando.y] < n->getMaxDistance()){
            for (int i = 0; i < 4; ++i) {
                sf::Vector2i aux = visitando;
                Direction d;
                switch (i%4) {
                case 0:
                    ++aux.x;
                    break;
                case 1:
                    --aux.x;
                    break;
                case 2:
                    ++aux.y;
                    break;
                case 3 :
                    --aux.y;
                    break;
                default:
                    break;
                }
                if (!visitado[aux.x][aux.y]) {
                    if (n->getMap()->isWalkeable(sf::Vector2f(aux.x,aux.y))) {
                        sinVisitar.push(aux);
                        printf("%i %i\n", aux.x, aux.y);
                        camino[aux.x][aux.y] = camino[visitando.x][visitando.y] + 1;
                        Terrain t = n->getMap()->getTerrain(aux.x,aux.y);
                        if(t.isPrinted()) {
                            t.setColor(sf::Color::Cyan);
                            mask.push_back(t);
                        }
                    }
                    visitado[aux.x][aux.y] = true;
                }
            }
        }
    }
}

