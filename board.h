#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"

class Board : public sf::Drawable
{
private:
    Map map;
//    Player players;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Board();
    void update(float deltaTime);
    void updateCamera(float deltaTime, sf::Vector2f dir);
    void updateNpc(float deltaTime, sf::Vector2f dir);
};

#endif // BOARD_H
