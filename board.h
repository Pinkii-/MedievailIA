#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"
#include "control.h"
#include "UI/display.h"
#include "Utils/util.h"
#include "Utils/Textures.hpp"
#include "UI/Interface.hpp"

class Board : public sf::Drawable
{
private:
    Map matrix;
    Control control;
	Textures texturas;
	Interface ui;
    Display displais;
    sf::Vector2f cameraPos;
	float cameraVel;
	sf::Vector2f cameraDir;
	float cameraWait;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Board();   
    void init();
    void update(float deltaTime);
    void updateD(float deltaTime, float deltaDraw);
	void updateCamera(float deltaTime);
	void updateDirCamera(sf::Vector2f d);  
    sf::Vector2f calculateColision(Npc n, float dt, sf::Vector2f dir);
    Control getControl();
};

#endif // BOARD_H
