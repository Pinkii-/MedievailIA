#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "terrain.h"
#include "display.h"
#include "npc.h"

#define WIDTH 1000
#define HEIGHT 600

#define ROWS 30
#define COLS 30

#define TILE_SIZE 40

#define NTEXTURES 3

enum texturas {
    tNone, tRock, tNpc
};


class Map : public sf::Drawable
{
private:
    std::vector<std::vector<Terrain> > matrix;
    std::vector<Npc> npcs;
    std::vector<std::vector<std::vector<std::vector<Way> > > > npcsCamino;
    std::vector<sf::Texture> texturas;

    sf::Vector2f cameraPos;
    sf::Vector2f cameraVel;

    Display displais;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Map();
    void init();
    void loadTextures();
    void generateMap();
    void loadMap();

    void npcInit();
    sf::Vector2f calculateColision(Npc n, float dt, sf::Vector2f dir);
    bool isWalkeable(sf::Vector2f pos);

    void update(float deltaTime);
    void updateCamera(float deltaTime, sf::Vector2f dir);
    void updateNpc(float deltaTime, sf::Vector2f dir);
    void updateDraw();
};

#endif // MAP_H
