#include "npc.h"

#include <iostream>

Npc::Npc()
{
}

Npc::Npc(sf::Texture* texturas, sf::Vector2f pos, int size, HitBox h) {
    this->setTexture(*texturas);
    posMatrix = pos;
    setPrinted(false);

    box = h;

    waiting = true;

    speed = 3;

}

void Npc::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

sf::Vector2f Npc::getMatPosition() {
    return posMatrix;
}

float Npc::getSpeed() {
    return speed;
}

HitBox Npc::getHitBox() {
    return box;
}

void Npc::update(float delta,Map &m) {
    delta *= speed;
    int i = 0;
    int max = 5;
    while (waiting and i < max) {
        dir = Direction(std::rand()%4); //Se elige la direccion que tiene que pillar para seguir la ruta
        sf::Vector2f vectorDirector = dirToVec(dir);
        ++i;
        if (m.isWalkeable(posMatrix+vectorDirector)) {
            waiting = false;
            sf::Vector2f dista = vectorDirector*delta;
            posMatrix += dista;
        }
    }
    if (i != max) {
        sf::Vector2f dist = dirToVec(dir)*delta;
        if (changingNumber(posMatrix.x,posMatrix.x+dist.x) or changingNumber(posMatrix.y,posMatrix.y+dist.y))  {
           posMatrix = vecfTrunc(posMatrix + dirNormaliced(dirToVec(dir)));
           waiting = true;
        }
        else posMatrix += dist;
    }
}
