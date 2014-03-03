#include "player.h"

Player::Player()
{
}

Player::Player(int nColor,Control* con) {
    c = con;
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
}
