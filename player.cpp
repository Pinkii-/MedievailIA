#include "player.h"
#include "control.h"
#include <stdio.h>

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    for (int i= buildings.size()-1; i >= 0; --i) {
        Base* building = buildings[i];
        target.draw(*building);
    }
    for (int i= npcs.size()-1; i >= 0; --i) {
        const Npc* npc = npcs[i];
        target.draw(*npc);
    }
}

Player::Player() {
}



void Player::init(int nColor,Control* con, Map* map) {
    c = con;
    m = map;
    switch (nColor) {
    case 0:
        color = sf::Color::Red;
        break;
    case 1:
        color = sf::Color::Cyan;
        break;
    case 2:
        color = sf::Color::Green;
        break;
    default:
        color = sf::Color::Black;
        break;
    }

    buildingInit();
    npcInit();
}

void Player::buildingInit() {
    sf::Vector2f pos = sf::Vector2f(3.0,3.0);
    Base* base = new Base(pos,TILE_SIZE);
    buildings.push_back(base);
}

void Player::npcInit() {
    //TODO Inicializacion de los npcs de cada jugador
    sf::Vector2f pos = sf::Vector2f(3.0,3.0);
    Npc* beta = new Npc(pos,TILE_SIZE, c, m);
    beta->setColor(sf::Color::White);
    beta->setPreference(Star);
    npcs.push_back(beta);
    //    Npc alfa(text,pos+sf::Vector2f(0,1),TILE_SIZE);
    //    npcs.push_back(alfa);
}

void Player::update(float deltaTime) {
    updateNpcs(deltaTime);
}

void Player::updateNpcs(float deltaTime) {
    for (unsigned int i = 0; i < npcs.size(); ++i) {
        npcs[i]->update(deltaTime);
    }
}

void Player::updateBuildings(float deltaTime) {
    for (unsigned int i = 0; i < buildings.size(); ++i) {
        buildings[i]->update(deltaTime);
    }
}

void Player::updateDraw() {
    for (unsigned int i= 0; i < npcs.size(); ++i) {
        sf::Vector2f posNpc = npcs[i]->getMatPosition();
        sf::Vector2f position;
        position.x = TILE_SIZE*(posNpc.x+UISPACE);
        position.y = TILE_SIZE*(posNpc.y);
        npcs[i]->setPosition(position);
    }
    for (unsigned int i= 0; i < buildings.size(); ++i) {
        sf::Vector2f posBuilding = buildings[i]->getMatPosition();
        sf::Vector2f position;
        position.x = TILE_SIZE*(posBuilding.x+UISPACE);
        position.y = TILE_SIZE*(posBuilding.y);
        buildings[i]->setPosition(position);
    }
}

void Player::addNpc() {
    Npc* npc = new Npc(buildings[0]->getMatPosition(),TILE_SIZE, c, m);
    npcs.push_back(npc);
}

std::vector<Npc*> Player::getNpcs(){
    return npcs;
}
