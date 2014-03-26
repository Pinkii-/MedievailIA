#include "control.h"
#include <math.h>
#include <iostream>


void Control::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    for (unsigned int i= 0; i < props.size(); ++i) {
        for (unsigned int j=0; j < props[i].size(); ++j) {
            const Prop* prop = &props[i][j];
            target.draw(*prop);

        }
    }
    for (unsigned int i = 0; i < players.size(); ++i) target.draw(players[i]);
}


Control::Control() {
}

void Control::init(Map* map) {
    m = map;
    props = std::vector<std::vector<Prop> >(NPROPS, std::vector<Prop> (0));
    players = std::vector<Player> (1);
    for (unsigned int  i = 0; i < players.size(); ++i) players[i].init(i,this,m);
}

void Control::update(float deltaTime, Map &m) {
    updateProp(m);
    for (unsigned int  i = 0; i < players.size(); ++i) players[i].update(deltaTime);
}

void Control::updateProp(Map &m) {
    //TODO a random generator of props on the map and check if is interacting with a NPC
    //TODO a random generator of props on the map
    //TODO a random generator of props on the map

    for (unsigned int i = 0; i < props.size(); ++i) {
        if (!props[i].empty()) npcOnProp(i);
        while (props[i].size() < 1 and std::rand()%10 == 0) {
            int x,y;
            x = std::rand() % COLS;
            y = std::rand() % ROWS;
            if (m.isWalkeable(sf::Vector2f(x,y))) {
                Prop p = Prop(Resource(Star+i),sf::Vector2f(x,y),TILE_SIZE);
                props[i].push_back(p);
            }
        }

    }
}

std::vector<sf::Vector2f> Control::getObjetiveNpc(Resource preference) {
    std::vector<sf::Vector2f> proppos;
    for (unsigned int j = 0; j < props.size(); ++j) {
        if (!props[j].empty() and props[j][0].getResource() == preference) {
            for (unsigned int k = 0; k < props[j].size(); ++k) {
                proppos.push_back(props[j][k].getMatPosition());
            }
        }
    }
    return proppos;
}



void Control::initDraw() {
    for (unsigned int i= 0; i < props.size(); ++i) {
        for (unsigned int j=0; j < props[i].size(); ++j) {
            sf::Vector2f posProp = props[i][j].getMatPosition();
            sf::Vector2f position;
            position.x = TILE_SIZE*(posProp.x+UISPACE);
            position.y = TILE_SIZE*(posProp.y);
            props[i][j].setPosition(position);

        }
    }
    for (unsigned int i = 0; i < players.size(); ++i) players[i].updateDraw();
}

void Control::erasePropN(std::vector<Prop> &v,int n) {
    Prop aux = v[n];
    v[n] = v[v.size()-1];
    v[v.size()-1]= aux;
    v.pop_back();
}

void Control::forceToUpdateObjective(sf::Vector2f pos) {
    for (unsigned int i = 0; i < players.size();++i) {
        std::vector<Npc*> npcs = players[i].getNpcs();
        for (unsigned int j = 0; j < npcs.size(); ++j) if (npcs[j]->getTargetDestination() == pos) npcs[j]->resetWay();
    }
}

Npc Control::getNpc(int player, int i) {
    return *players[player].getNpcs()[i];
}

Player Control::getPlayer() {
    return players[0];
}

bool Control::npcOnProp(int j) {
    for (unsigned int p = 0; p < players.size(); ++p) {
        std::vector<Npc*> npcs = players[p].getNpcs();
        for (unsigned int i = 0; i < npcs.size(); ++i) {
            for (unsigned int k = 0; k < props[j].size(); ++k) {
                if (npcs[i]->getMatPosition() == props[j][k].getMatPosition() and npcs[i]->getPreference() == props[j][k].getResource()) {
                    // TODO: Set the behavior between the npc and the prop

                    forceToUpdateObjective(props[j][k].getMatPosition());
                    //				 Npc npc(props[j][k].getMatPosition(),TILE_SIZE,this);
                    //				 npc.setWaitTime(std::min(int(npcs.size()),20)*0.1);

                    //				 std::cout << std::min(int(npcs.size()),25) << std::endl;

                    ////				 if (npcs[i].getPreference() == Star) {
                    ////					 npcs[i].setColor(sf::Color::Black);
                    ////					 npcs[i].setPreference(BStar);
                    ////					 npc.setPreference(Star);
                    ////					 npc.setColor(sf::Color::Yellow);
                    ////				 }
                    ////				 else {
                    ////					 npcs[i].setPreference(Star);
                    ////					 npcs[i].setColor(sf::Color::Yellow);
                    ////					 npc.setColor(sf::Color::Black);
                    ////					 npc.setPreference(BStar);
                    ////				 }

                    //				 npc.setColor(getColor(npcs.size()));
                    //				 npcs.push_back(npc);

                    //players[p].addNpc();
                    //players[p].getNpcs()[players[p].getNpcs().size()-1]->setWaitTime(0.1f); // oh GOD
                    erasePropN(props[j],k);
                    return true;
                }
            }
        }
    }
    return false;
}


