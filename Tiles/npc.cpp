#include "npc.h"

#include <iostream>
#include <queue>
#include <stack>

#include "control.h"



Npc::Npc()
{
}

Npc::Npc(sf::Vector2f pos, int size, Control* con, Map* map) : c(con), m(map) {
	this->setTexture(Textures::npc);

    float scalex, scaley;
	scalex =  size/float(this->getTexture()->getSize().x);
	scaley =  size/float(this->getTexture()->getSize().y);

    this->setScale(scalex,scaley);

    posMatrix = pos;
    setPrinted(false);
    waiting = true;
    speed = 10;
    waitTime = 0;
    maxDistance = 1;

    initPreferences();
	goingTo = *preferences.begin();
}

void Npc::initPreferences() {
    for (int i = 0; i < NPROPS; ++i) {
        preferences.push_back(Star+i);
    }
}

void Npc::update(float delta) {
//	way = std::queue<Direction>();
    waitTime -= delta;
    int i = 0;
    int max = 5;
    while (waiting and i < max and waitTime <= 0) {
        ++i;
        if(!way.empty()) {
            maxDistance = 1;
            dir = way.front();
            sf::Vector2f vectorDirector = dirToVec(dir);
            sf::Vector2f dista = vectorDirector*speed*delta;
            posMatrix += dista;
            waiting = false;
        }
        else {
            std::list<Resource>::iterator it = preferences.begin();;
            while (way.empty() and it != preferences.end()) {
                posDestino = c->getObjetiveNpc(*it);
                if (!posDestino.empty()) {
                    calculateWay();
                    if (!way.empty()) {
                        goingTo = *it;
                        break;
                    }
                }
                ++it;
            }
            if (it == preferences.end() and way.empty()) {
                ++maxDistance;
                waitTime = 0.1;
            }
        }
    }
    if (i != max and waitTime <= 0) {
        sf::Vector2f dist = dirToVec(dir)*speed*delta;
        if (changingNumber(posMatrix.x,posMatrix.x+dist.x) or changingNumber(posMatrix.y,posMatrix.y+dist.y))  {
           posMatrix = vecfTrunc(posMatrix + dirNormaliced(dirToVec(dir)));
            waiting = true;
           if (!way.empty()) way.pop();
        }
        else posMatrix += dist;
    }
}

void Npc::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

void Npc::setDesPosition(std::vector<sf::Vector2f> pos) {
    posDestino = pos;
}

void Npc::decrementSpeed() {
    speed -= 0.5;
}

void Npc::setWaitTime(float time) {
    waitTime = time;
}

void Npc::calculateWay() { /// From ini to dest
    std::vector<std::vector<bool> > visitado(COLS, std::vector<bool>(ROWS,false));
    std::vector<std::vector<Way> > camino(COLS, std::vector<Way>(ROWS));
    std::queue<sf::Vector2i> sinVisitar;
    if (posDestino.size() == 0) std::cout << "LLorar" << std::endl;
    visitado[int(posMatrix.x)][int(posMatrix.y)] = true;
    camino[int(posMatrix.x)][int(posMatrix.y)].dist = 0;
    sinVisitar.push(vecfToVeci(posMatrix));
    while (!sinVisitar.empty() and not isOnDest(sinVisitar.front())) {
        sf::Vector2i visitando = sinVisitar.front();
        sinVisitar.pop();

        if (maxDistance != 0 and maxDistance < camino[visitando.x][visitando.y].dist) break;
		int rand = std::rand()%4;
        for (int i = 0+rand; i < 4+rand;++i) {
            sf::Vector2i aux = visitando;
            Direction d;
            switch (i%4) {
            case 0:
                ++aux.x;
                d = Right;
                break;
            case 1:
                --aux.x;
                d = Left;
                break;
            case 2:
                ++aux.y;
                d = Down;
                break;
            case 3 :
                --aux.y;
                d = Up;
                break;
            default:
                break;
            }
            if (!visitado[aux.x][aux.y]) {
                if (m->isWalkeable(sf::Vector2f(aux.x,aux.y))) {
                    sinVisitar.push(aux);
                    camino[aux.x][aux.y].dir = d;
                    camino[aux.x][aux.y].dist = ++camino[visitando.x][visitando.y].dist +1 ;
                }
                visitado[aux.x][aux.y] = true;
            }
        }
    }

    if (isOnDest(sinVisitar.front())) {
        std::stack<Direction> aux;
        sf::Vector2i pos = vecfToVeci(posDestino[0]);

        while (pos != vecfToVeci(posMatrix)) {
            aux.push(camino[pos.x][pos.y].dir);
            pos += vecfToVeci(dirToVec(opposite(camino[pos.x][pos.y].dir)));
        }
        while (!aux.empty()) { /// Have to swap all the elements
            way.push(aux.top());
            aux.pop();
        }
    }
}

void Npc::setPreference(Resource p) {
    preferences.remove(p);
    preferences.push_front(p);
    way = std::queue<Direction>();
}

// If dist = 0, it means that the npc will try to reach any position of the map.
// Otherwise, it will try to reach only the first "dist" tiles.
void Npc::setMaxDistance(int dist) {
    maxDistance = dist;
}

Resource Npc::getPreference() {
  return goingTo;
}

sf::Vector2f Npc::getMatPosition() {
    return posMatrix;
}

int Npc::getMaxDistance() {
    return maxDistance;
}

Map* Npc::getMap() {
    return m;
}

bool Npc::isOnDest(sf::Vector2i n) {
    sf::Vector2f aux;
    for (unsigned int i = 0; i < posDestino.size(); ++i) {
        if (n == vecfToVeci(posDestino[i])) {
            aux = posDestino[i];
            posDestino.clear();
            posDestino.push_back(aux);
            return true;
        }
    }
    return false;
}

//bool Npc::checkWay(Map &m) {
//    if (way.empty()) {
//        waiting = true;
//        return false;
//    }
//    std::stack<Direction> aux = std::stack<Direction>(way);
//    sf::Vector2f pos = absoluteValue(posMatrix);
//    while (!aux.empty()) {
//        Direction d = aux.top();
//        aux.pop();
//        std::cout << pos.x << " " << pos.y << std::endl;
//        pos = pos+d;
//        std::cout << pos.x << " " << pos.y << std::endl;
//        if (!m.isWalkeable(pos)) {
//            std::cout << "No es walkeable" << std::endl;
//            way = std::stack<Direction>();
//            return false;
//        }
//    }
//    return true;
//}

float Npc::getSpeed() {
    return speed;
}

// annie waits - Rockin' the suburs - Ben folds
// ants marching (acoustic) house of blues - Dave Matthews Band
// armando la llamada
