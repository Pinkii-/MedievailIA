#include "control.h"

Control::Control()
{
}

Control::Control(std::vector<sf::Texture> *text) {
    texturas = *text;
    props = std::vector<Prop> (0);
    npcs = std::vector<Npc> (0);
}

void Control::npcInit() {
    //TODO Inicializacion de los npcs de cada jugador
    sf::Texture* text = &texturas[tNpc];
    sf::Vector2f pos = sf::Vector2f(3.0,3.0);
    Npc beta(text,pos,TILE_SIZE);
    beta.setColor(sf::Color::Black);
    npcs.push_back(beta);
//    Npc alfa(text,pos+sf::Vector2f(0,1),TILE_SIZE);
//    npcs.push_back(alfa);
}

void Control::update(float deltaTime, Map &m) {
    updateProp(deltaTime,m);
    updatePosNpc(deltaTime,m);
}

void Control::updateProp(float deltaTime,Map &m) {
    //TODO a random generator of props on the map

    if (props.size() > 0 and npcOnProp(deltaTime)) props.clear();

    while (props.size() == 0) {
        int x,y;
        x = std::rand() % COLS;
        y = std::rand() % ROWS;
        if (m.isWalkeable(sf::Vector2f(x,y))) {
            sf::Texture *text = &texturas[tStar];
            Prop p = Prop(Star,text,sf::Vector2f(x,y),TILE_SIZE);
            props.push_back(p);
        }
    }

    updateObjetiveNpc(props[0].getMatPosition());
}

void Control::updateObjetiveNpc(sf::Vector2f pos) {
    for (unsigned int i = 0; i < npcs.size(); ++i) {
        npcs[i].setDesPosition(pos);
    }
}

void Control::updatePosNpc(float deltaTime, Map &m) {
    for (unsigned int i = 0; i < npcs.size(); ++i) {
        npcs[i].update(deltaTime,m);
    }
}

void Control::updateDraw(sf::Vector2f cameraPos) {
    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;
    for (unsigned int i= 0; i < props.size(); ++i) {
        sf::Vector2f posProp = props[i].getMatPosition();
        if (posProp.x >= cameraPos.x-1 and posProp.x < cameraPos.x + sizex + 1 and posProp.y >= cameraPos.y-1 and posProp.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posProp.x-cameraPos.x);
            position.y = TILE_SIZE*(posProp.y-cameraPos.y);
            props[i].setPosition(position);
            props[i].setPrinted(true);
        }
        else props[i].setPrinted(false);
    }
    for (unsigned int i= 0; i < npcs.size(); ++i) {
        sf::Vector2f posNpc = npcs[i].getMatPosition();
        if (posNpc.x >= cameraPos.x-1 and posNpc.x < cameraPos.x + sizex + 1 and posNpc.y >= cameraPos.y-1 and posNpc.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posNpc.x-cameraPos.x);
            position.y = TILE_SIZE*(posNpc.y-cameraPos.y);
            npcs[i].setPosition(position);
            npcs[i].setPrinted(true);
        }
        else npcs[i].setPrinted(false);
    }
}

void Control::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (unsigned int i= 0; i < props.size(); ++i) {
        if (props[i].isPrinted()) {
            const Prop* prop = &props[i];
            target.draw(*prop);
        }
    }
    for (int i= npcs.size()-1; i >= 0; --i) {
        if (npcs[i].isPrinted()) {
            const Npc* npc = &npcs[i];
            target.draw(*npc);
        }
    }
}

 Npc Control::getNpc(int i) {
     return npcs[i];
 }

 bool Control::npcOnProp(float deltaTime) {
     for (unsigned int i = 0; i < npcs.size(); ++i) {
         if (npcs[i].getMatPosition() == props[0].getMatPosition()) {
             sf::Texture *text = &texturas[tNpc];
             Npc npc(text,props[0].getMatPosition(),TILE_SIZE);
             npc.setWaitTime(0.1*npcs.size());
             npcs.push_back(npc);
             return true;
         }
     }
     return false;
 }
