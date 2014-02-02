#include "board.h"

Board::Board()
{
    map.init();
}



void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(map);
}

void Board::update(float deltaTime) {
    map.updateDraw();
    map.update(deltaTime);
}

void Board::updateCamera(float deltaTime, sf::Vector2f dir) {
    map.updateCamera(deltaTime,dir);
}

void Board::updateNpc(float deltaTime, sf::Vector2f dir) {
    map.updateNpc(deltaTime,dir);
}

