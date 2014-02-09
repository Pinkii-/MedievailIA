#include "npc.h"

#include <iostream>
#include <queue>

Npc::Npc()
{
}

Npc::Npc(sf::Texture* texturas, sf::Vector2f pos, int size) {
    this->setTexture(*texturas);

    float scalex, scaley;
    scalex =  size/float(texturas->getSize().x);
    scaley =  size/float(texturas->getSize().y);

    this->setScale(scalex,scaley);

    posMatrix = pos;
    setPrinted(false);
    waiting = true;
    speed = 4;
    waitTime = 0;

    initPreferences();
}

void Npc::initPreferences() {
//    for (int i = 0; i < NPROPS; ++i) {
//        preferences.push_back(i);
//    }
    preferences.push_back(Star);
}

TypoP Npc::getPreference() {
    std::list<TypoP>::iterator it = preferences.begin();
    return *it;
}

void Npc::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

void Npc::setDesPosition(std::vector<sf::Vector2f> pos) {
    posDestino = pos;
}

sf::Vector2f Npc::getMatPosition() {
    return posMatrix;
}

float Npc::getSpeed() {
    return speed;
}

void Npc::decrementSpeed() {
    speed -= 0.5;
}

void Npc::setWaitTime(float time) {
    waitTime = time;
}

void Npc::update(float delta,Map &m) {
    waitTime -= delta;
    delta *= speed;
    int i = 0;
    int max = 5;
    //way = std::stack<Direction>();
    while (waiting and i < max and waitTime <= 0) {
        ++i;
        if(!way.empty()) {
            dir = way.top();
            sf::Vector2f vectorDirector = dirToVec(dir);
            sf::Vector2f dista = vectorDirector*delta;
            posMatrix += dista;
            waiting = false;
        }
        else {
            calculateWay(m);
//            dir = Direction(std::rand()%4); //Se elige la direccion que tiene que pillar para seguir la ruta
//            sf::Vector2f vectorDirector = dirToVec(dir);
//            if (m.isWalkeable(posMatrix+vectorDirector)) {
//                waiting = false;
//                sf::Vector2f vectorDirector = dirToVec(dir);
//                sf::Vector2f dista = vectorDirector*delta;
//                posMatrix += dista;
//            }

        }
    }
    if (i != max and waitTime <= 0) {
        sf::Vector2f dist = dirToVec(dir)*delta;
        if (changingNumber(posMatrix.x,posMatrix.x+dist.x) or changingNumber(posMatrix.y,posMatrix.y+dist.y))  {
           posMatrix = vecfTrunc(posMatrix + dirNormaliced(dirToVec(dir)));
            waiting = true;
           if (!way.empty()) way.pop();
        }
        else posMatrix += dist;
    }
}

void Npc::calculateWay(Map &m) {
    std::vector<std::vector<bool> > visitado(COLS, std::vector<bool>(ROWS,false));
    std::vector<std::vector<Direction> > camino(COLS, std::vector<Direction>(ROWS));
    std::queue<sf::Vector2i> sinVisitar;
    if (posDestino.size() == 0) std::cout << "LLorar" << std::endl;
    visitado[int(posDestino[0].x)][int(posDestino[0].y)] = true;
    sinVisitar.push(vecfToVeci(posDestino[0]));
    while (!sinVisitar.empty() and sinVisitar.front() != vecfToVeci(posMatrix)) {
        sf::Vector2i visitando = sinVisitar.front();
        sinVisitar.pop();
        int rand = std::rand()%4;
        for (int i = 0+rand; i < 4+rand;++i) {
            sf::Vector2i aux = visitando;
            Direction d;
            switch (i%4) { // The direction have to be the opposite direction because the route is on the opposite direction
            case 0:
                ++aux.x;
                d = Left;
                break;
            case 1:
                --aux.x;
                d = Right;
                break;
            case 2:
                ++aux.y;
                d = Up;
                break;
            case 3 :
                --aux.y;
                d = Down;
                break;
            default:
                break;
            }
            if (!visitado[aux.x][aux.y]) {
                if (m.isWalkeable(sf::Vector2f(aux.x,aux.y))) {
                    camino[aux.x][aux.y] = d;
                    sinVisitar.push(aux);
                }
                visitado[aux.x][aux.y] = true;
            }
        }
    }
    std::stack<Direction> aux;
    sf::Vector2i pos = vecfToVeci(posMatrix);
    while (pos != vecfToVeci(posDestino[0])) {
        aux.push(camino[pos.x][pos.y]);
        pos += vecfToVeci(dirToVec(camino[pos.x][pos.y]));
    }
    while (!aux.empty()) {
        way.push(aux.top());
        aux.pop();
    }
}

bool Npc::checkWay(Map &m) {
    if (way.empty()) {
        waiting = true;
        return false;
    }
    std::stack<Direction> aux = std::stack<Direction>(way);
    sf::Vector2f pos = absoluteValue(posMatrix);
    while (!aux.empty()) {
        Direction d = aux.top();
        aux.pop();
        std::cout << pos.x << " " << pos.y << std::endl;
        pos = pos+d;
        std::cout << pos.x << " " << pos.y << std::endl;
        if (!m.isWalkeable(pos)) {
            std::cout << "No es walkeable" << std::endl;
            way = std::stack<Direction>();
            return false;
        }
    }
    return true;
}



// annie waits - Rockin' the suburs - Ben folds
// ants marching (acoustic) house of blues - Dave Matthews Band
// armando la llamada
