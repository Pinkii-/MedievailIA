#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"
#include "control.h"
#include "display.h"
#include "util.h"
#include "Textures.hpp"
#include "Interface.hpp"

class Board : public sf::Drawable
{
private:
    Map matrix;
    Control control;
	Textures texturas;
	Interface ui;

    sf::Vector2f cameraPos;
	float cameraVel;
	sf::Vector2f cameraDir;
	float cameraWait;

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
	void updateCamera(float deltaTime);
	void updateDirCamera(sf::Vector2f d);
};

#endif // BOARD_H
