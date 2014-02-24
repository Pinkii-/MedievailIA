#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"
#include "control.h"
#include "display.h"
#include "util.h"
#include "Textures.hpp"

class Board : public sf::Drawable
{
private:
    Map matrix;
    Control control;
    //Map<Map<Way> > npcsCamino;
	Textures texturas;

    sf::Vector2f cameraPos;
	float cameraVel;

    Display displais;
//    Player players;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Board();
    void init();
    void loadTextures();


    sf::Vector2f calculateColision(Npc n, float dt, sf::Vector2f dir);

    void update(float deltaTime);
    void updateD(float deltaTime, float deltaDraw);
    void updateCamera(float deltaTime, sf::Vector2f dir);
};

#endif // BOARD_H
