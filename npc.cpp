#include "npc.h"
#include "control.h"

#include <iostream>
#include <queue>
#include <stack>

Npc::Npc()
{
}

Npc::Npc(sf::Texture* texturas, sf::Vector2f pos, int size, Control* con) : c(con) {
    this->setTexture(*texturas);

    float scalex, scaley;
    scalex =  size/float(texturas->getSize().x);
    scaley =  size/float(texturas->getSize().y);

    this->setScale(scalex,scaley);

    posMatrix = pos;
    setPrinted(false);
    waiting = true;
	speed = 50;
    waitTime = 0;

    initPreferences();
}

void Npc::initPreferences() {
    for (int i = 0; i < NPROPS; ++i) {
        preferences.push_back(Star+i);
    }
}

void Npc::setPreference(TypoP p) {
	preferences.remove(p);
	preferences.push_front(p);
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
//	way = std::queue<Direction>();
    --waitTime;
    int i = 0;
    int max = 5;
    while (waiting and i < max and waitTime <= 0) {
        ++i;
        if(!way.empty()) {
            dir = way.front();
            sf::Vector2f vectorDirector = dirToVec(dir);
			sf::Vector2f dista = vectorDirector*speed*delta;
            posMatrix += dista;
            waiting = false;
        }
        else {
			for (std::list<TypoP>::iterator it = preferences.begin(); it != preferences.end(); ++it) {
				posDestino = c->getObjetiveNpc(*it);
				if (!posDestino.empty()) break;
			}
            calculateWay(m);
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

void Npc::calculateWay(Map &m) { /// From ini to dest
    std::vector<std::vector<bool> > visitado(COLS, std::vector<bool>(ROWS,false));
    std::vector<std::vector<Direction> > camino(COLS, std::vector<Direction>(ROWS));
    std::queue<sf::Vector2i> sinVisitar;
    if (posDestino.size() == 0) std::cout << "LLorar" << std::endl;
    visitado[int(posMatrix.x)][int(posMatrix.y)] = true;
    sinVisitar.push(vecfToVeci(posMatrix));
    while (!sinVisitar.empty() and not isOnDest(sinVisitar.front())) {
        sf::Vector2i visitando = sinVisitar.front();
        sinVisitar.pop();
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
                if (m.isWalkeable(sf::Vector2f(aux.x,aux.y))) {
                    sinVisitar.push(aux);
                    camino[aux.x][aux.y] = d;
                }
                visitado[aux.x][aux.y] = true;
            }
        }
    }
    std::stack<Direction> aux;
    sf::Vector2i pos = vecfToVeci(posDestino[0]);

     while (pos != vecfToVeci(posMatrix)) {
        aux.push(camino[pos.x][pos.y]);
        pos += vecfToVeci(dirToVec(opposite(camino[pos.x][pos.y])));
    }
    while (!aux.empty()) { /// Have to swap all the elements
        way.push(aux.top());
        aux.pop();
    }
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



// annie waits - Rockin' the suburs - Ben folds
// ants marching (acoustic) house of blues - Dave Matthews Band
// armando la llamada
