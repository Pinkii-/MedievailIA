#include <iostream>
#include <fstream>

#include "map.h"

Map::Map() {}

void Map::init() {
    cameraPos = sf::Vector2f(0.0,0.0);
    cameraVel = sf::Vector2f(30,30);
    texturas = std::vector<sf::Texture> (NTEXTURES);
    loadTextures();
    // creacion de estructuras de datos
    matrix = std::vector<std::vector<Terrain> > (COLS,(std::vector<Terrain>(ROWS)));
    npcs = std::vector<Npc> (0);
    // inicializaciones de estructuras de datos
    generateMap();
    displais.init();
    npcInit();
    updateCamera(0,sf::Vector2f(0,0)); //despues de dibujar todo

    npcsCamino = std::vector<std::vector<std::vector<std::vector<Way> > > >
            (COLS, (std::vector<std::vector<std::vector<Way> > >
                    (ROWS, std::vector<std::vector<Way> >
                     (COLS, (std::vector<Way>
                             (ROWS))))));
}

void Map::loadTextures() {
    //Terrain Textures
    texturas[tNone].loadFromFile("Resources/pruebaTile.png");
    texturas[tRock].loadFromFile("Resources/pruebaTile2.png");

    //NPC Textures
    texturas[tNpc].loadFromFile("Resources/npc.png");

}

void Map::generateMap() {
//    for (unsigned int i = 0; i < matrix.size(); ++i) {
//        for (unsigned int j = 0; j < matrix[0].size(); ++j) {
//            Typo p;
//            if (i == 0 or j == 0 or i == matrix.size()-1 or j == matrix[0].size() -1) p = Rock;
//            else p = None;
//            sf::Texture* textura = &texturas[p];
//            matrix[i][j] = Terrain(p,textura,TILE_SIZE);
//        }
//    }

    loadMap();
}

void Map::loadMap() {


    std::string map = "mapa";
    std::string auxS = "Resources/"+map+".txt";
    std::ifstream myfile;
    myfile.open(auxS.c_str());

    char c;
    const char cNone = '.';
    const char cRock = 'X';

    unsigned int i = 0;
    unsigned int j = 0;

    while (myfile >> c) {
        Typo typo;
        switch (c) {
        case cNone:
            typo = None;
            break;
        case cRock:
            typo = Rock;
            break;
        default:
            std::perror("Error");
            typo = None;
            break;
        }
        sf::Texture* textura = &texturas[typo];
        matrix[j][i] = Terrain(typo,textura,TILE_SIZE);
        ++j;
        if (j >= matrix[0].size()) {
            j = 0;
            ++i;
        }

    }
    myfile.close();
}

void Map::npcInit() {
    //TODO Inicializacion de los npcs de cada jugador
    sf::Texture* text = &texturas[tNpc];
    sf::Vector2f pos = sf::Vector2f(3.0,3.0);
    HitBox b;
    b.minX = 8;
    b.maxX = 32;
    b.minY = 5;
    b.maxY = 36;
    Npc beta(text,pos,TILE_SIZE, b);
    npcs.push_back(beta);

}

sf::Vector2f Map::calculateColision(Npc n, float dt, sf::Vector2f dir) {
    sf::Vector2f pos = n.getMatPosition();
    sf::Vector2f speed = n.getSpeed();
    pos.x += dir.x*speed.x*dt;
    pos.y += dir.y*speed.y*dt;

    bool MatPos= false;

    sf::Vector2f posAux = n.getPosition();
    if (dir.x == 1) {
        posAux.x += n.getHitBox().maxX;
        posAux.y += n.getHitBox().maxY;
        if (!isWalkeable(posAux)) MatPos = true;
        posAux.y = n.getPosition().y + n.getHitBox().minY;
        if (!isWalkeable(posAux)) MatPos = true;
    }
    if (dir.x == -1) {
        posAux.x += n.getHitBox().minX;
        posAux.y += n.getHitBox().maxY;
        if (!isWalkeable(posAux)) MatPos = true;
        posAux.y = n.getPosition().y + n.getHitBox().minY;
        if (!isWalkeable(posAux)) MatPos = true;
    }
    if (dir.y == 1) {
        posAux.y += n.getHitBox().maxY;
        posAux.x += n.getHitBox().maxX;
        if (!isWalkeable(posAux)) MatPos = true;
        posAux.x = n.getPosition().x + n.getHitBox().minX;
        if (!isWalkeable(posAux)) MatPos = true;
    }
    if (dir.y == -1) {
        posAux.y += n.getHitBox().minY;
        posAux.x += n.getHitBox().maxX;
        if (!isWalkeable(posAux)) MatPos = true;
        posAux.x = n.getPosition().x + n.getHitBox().minX;
        if (!isWalkeable(posAux)) MatPos = true;
    }
    if (MatPos) return n.getMatPosition();
    return pos;
}

bool Map::isWalkeable(sf::Vector2f pos) {
    int x = pos.x/TILE_SIZE;
    int y = pos.y/TILE_SIZE;

    if (matrix[x][y].getTypo() == None) return true;
    else return false;
}

void Map::update(float deltaTime) {
    displais.update(deltaTime,cameraPos,npcs[0].getPosition());
}

void Map::updateCamera(float deltaTime, sf::Vector2f dir) {
    cameraPos.x += dir.x*cameraVel.x*deltaTime;
    cameraPos.y += dir.y*cameraVel.y*deltaTime;
    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;
    if (cameraPos.x < 0) cameraPos.x = 0;
    else if(cameraPos.x >= COLS - sizex) cameraPos.x = COLS - sizex;
    if (cameraPos.y < 0) cameraPos.y = 0;
    else if(cameraPos.y >= ROWS - sizey) cameraPos.y = ROWS - sizey;
}

void Map::updateNpc(float deltaTime, sf::Vector2f dir) {
    sf::Vector2f pos = calculateColision(npcs[0], deltaTime, dir);
    if (pos.x < 0) pos.x = 0;
    else if(pos.x >= COLS) pos.x = COLS;
    if (pos.y < 0) pos.y = 0;
    else if(pos.y >= ROWS) pos.y = ROWS;

    npcs[0].setMatPosition(pos);
}

void Map::updateDraw() {
    int sizei = matrix.size();
    int sizej = matrix[0].size();

    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;

    for (int i = 0; i < sizei; ++i) {
        for (int j = 0; j < sizej; ++j) {
            if (i >= cameraPos.x-1 and i < cameraPos.x + sizex + 1 and j >= cameraPos.y-1 and j < cameraPos.y+sizey+1) {

                sf::Vector2f position;
                position.x = TILE_SIZE*(float(i)-cameraPos.x);
                position.y = TILE_SIZE*(float(j)-cameraPos.y);

                matrix[i][j].setPosition(position);
                matrix[i][j].setPrinted(true);
                //Intercalando colores para apreciar mejor el movimiento
                if ((j + i)%2 == 0) matrix[i][j].setColor(sf::Color(125,125,125,255));
                else matrix[i][j].setColor(sf::Color(0,255,0,255));
            }
            else matrix[i][j].setPrinted(false);
        }
    }

    for (unsigned int i= 0; i < npcs.size(); ++i) {
        sf::Vector2f posNpc = npcs[i].getMatPosition();
        if (posNpc.x >= cameraPos.x-1 and posNpc.x < cameraPos.x + sizex + 1 and posNpc.y >= cameraPos.y-1 and posNpc.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posNpc.x-cameraPos.x);
            position.y = TILE_SIZE*(posNpc.y-cameraPos.y);
            npcs[i].setPosition(position);
            npcs[i].setPrinted(true);
        }
        else npcs[i].setPrinted(false);
    }

}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    int sizei = matrix.size();
    int sizej = matrix[0].size();
    for (int i = 0; i < sizei; ++i) {
        for (int j = 0; j < sizej; ++j) {
            if (matrix[i][j].isPrinted()) {
                const Tile* tile = &matrix[i][j];
                target.draw(*tile);
            }
        }
    }
    for (unsigned int i= 0; i < npcs.size(); ++i) {
        if (npcs[i].isPrinted()) {
            const Npc* npc = &npcs[i];
            target.draw(*npc);
        }
    }
    target.draw(displais);
}
