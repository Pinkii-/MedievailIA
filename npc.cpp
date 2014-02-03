#include "npc.h"

Npc::Npc()
{
}

Npc::Npc(sf::Texture* texturas, sf::Vector2f pos, int size, HitBox h) {
    this->setTexture(*texturas);
    posMatrix = pos;
    setPrinted(false);

    box = h;

    waiting = true;

    speed = sf::Vector2f(3.0,3.0);

}

void Npc::setMatPosition(sf::Vector2f pos) {
    posMatrix = pos;
}

sf::Vector2f Npc::getMatPosition() {
    return posMatrix;
}

sf::Vector2f Npc::getSpeed() {
    return speed;
}

HitBox Npc::getHitBox() {
    return box;
}

//void Npc::update(Map<Terrain> &m) {
//    while (waiting) {
//        Direction dir = Direction(std::rand()%4);
//        switch (dir) {
//        case Up:
//            if ()
//            break;
//        default:
//            break;
//        }
//    }
//}
