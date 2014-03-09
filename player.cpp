#include "player.h"
#include "control.h"

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i= buildings.size()-1; i >= 0; --i) {
        if (buildings[i]->isPrinted()) {
            const Base* building = buildings[i];
            target.draw(*building);
        }
    }
    for (int i= npcs.size()-1; i >= 0; --i) {
        if (npcs[i]->isPrinted()) {
            const Npc* npc = npcs[i];
            target.draw(*npc);
        }
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

void Player::updateDraw(sf::Vector2f cameraPos) {
    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;
    for (unsigned int i= 0; i < npcs.size(); ++i) {
        sf::Vector2f posNpc = npcs[i]->getMatPosition();
        if (posNpc.x >= cameraPos.x-1 and posNpc.x < cameraPos.x + sizex + 1 - UISPACE and posNpc.y >= cameraPos.y-1 and posNpc.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posNpc.x+UISPACE-cameraPos.x);
            position.y = TILE_SIZE*(posNpc.y-cameraPos.y);
            npcs[i]->setPosition(position);
            npcs[i]->setPrinted(true);
        }
        else npcs[i]->setPrinted(false);
    }
    for (unsigned int i= 0; i < buildings.size(); ++i) {
        sf::Vector2f posBuilding = buildings[i]->getMatPosition();
        if (posBuilding.x >= cameraPos.x-1 and posBuilding.x < cameraPos.x + sizex + 1 - UISPACE and posBuilding.y >= cameraPos.y-1 and posBuilding.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posBuilding.x+UISPACE-cameraPos.x);
            position.y = TILE_SIZE*(posBuilding.y-cameraPos.y);
            buildings[i]->setPosition(position);
            buildings[i]->setPrinted(true);
        }
        else buildings[i]->setPrinted(false);
    }
}

void Player::addNpc() {
	Npc* npc = new Npc(sf::Vector2f(3.f,3.f),TILE_SIZE, c, m);
	npcs.push_back(npc);
}

std::vector<Npc*> Player::getNpcs(){
    return npcs;
}
