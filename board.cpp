#include "board.h"
#include "map.cpp"

Board::Board()
{
}

void Board::init() {
    cameraPos = sf::Vector2f(0.0,0.0);
    cameraVel = sf::Vector2f(30,30);
    texturas = std::vector<sf::Texture> (NTEXTURES);
    loadTextures();
    // creacion de estructuras de datos
    matrix = Map(COLS,ROWS, &texturas);
    npcs = std::vector<Npc> (0);
    // inicializaciones de estructuras de datos
    matrix.generateMap();
    matrix.generateBfs();
    displais.init();
    npcInit();
    updateCamera(0,sf::Vector2f(0,0)); //despues de dibujar todo

    //npcsCamino = Map<Map<Way> >();
}

void Board::loadTextures() {
    //Terrain Textures
    texturas[tNone].loadFromFile("Resources/pruebaTile.png");
    texturas[tRock].loadFromFile("Resources/pruebaTile2.png");

    //NPC Textures
    texturas[tNpc].loadFromFile("Resources/npc.png");
}

void Board::npcInit() {
    //TODO Inicializacion de los npcs de cada jugador
    sf::Texture* text = &texturas[tNpc];
    sf::Vector2f pos = sf::Vector2f(3.0,3.0);
    Npc beta(text,pos,TILE_SIZE);
    npcs.push_back(beta);
    Npc alfa(text,pos+sf::Vector2f(3,3),TILE_SIZE);
    npcs.push_back(alfa);
}

sf::Vector2f Board::calculateColision(Npc n, float dt, sf::Vector2f dir) {

    /* This shit should work, but by now it doesnt. So let's try to not look at it (/-_-)/ */

    sf::Vector2f pos = n.getMatPosition();
    float speed = n.getSpeed();
    pos.x += dir.x*speed*dt;
    pos.y += dir.y*speed*dt;

    bool MatPos= false;
    const sf::Vector2f constposAux = n.getMatPosition();
    sf::Vector2f posAux = constposAux;
    float hbMaxX = n.getHitBox().maxX/float(TILE_SIZE);
    float hbMinX = n.getHitBox().minX/float(TILE_SIZE);
    float hbMaxY = n.getHitBox().maxY/float(TILE_SIZE);
    float hbMinY = n.getHitBox().minY/float(TILE_SIZE);
//    std::cout << std::end;
//    std::cout << "x: " << n.getMatPosition().x * TILE_SIZE << " y: " << n.getMatPosition().y * TILE_SIZE<< std::endl;
//    std::cout << "X: " << pos.x * TILE_SIZE                << " Y: " << pos.y * TILE_SIZE               << std::endl;
    if (dir.x == 1) {
        posAux.x += hbMaxX;
        posAux.y += hbMaxY;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        posAux.y = constposAux.y + hbMinY;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        if(MatPos) pos.x = int(n.getMatPosition().x) + 1 - hbMaxX;
//        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " xs " << posAux.x << " " << int(posAux.x) << std::endl;
    }
    posAux = constposAux;
    if (dir.x == -1) {
        posAux.x += hbMinX;
        posAux.y += hbMaxY;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        posAux.y = constposAux.y + hbMinY;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        if(MatPos) pos.x = int(n.getMatPosition().x) + 1 - hbMinX;
//        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " xs " << posAux.x << " " << int(posAux.x) << std::endl;
    }
    posAux = constposAux;
    if (dir.y == 1) {
        posAux.y += hbMaxY;
        posAux.x += hbMaxX;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        posAux.x = constposAux.x + hbMinX;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        if(MatPos) pos.y = int(n.getMatPosition().y) + 1 - hbMaxY;
//        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " ys " << posAux.y << " " << int(posAux.y) << std::endl;
    }
    posAux = constposAux;
    if (dir.y == -1) {
        posAux.y += hbMinY;
        posAux.x += hbMaxX;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        posAux.x = constposAux.x + hbMinX;
        if (!matrix.isWalkeable(posAux)) MatPos = true;
        if(MatPos) pos.y = int(n.getMatPosition().y) + 1 - hbMinY;
//        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " ys " << posAux.y << " " << int(posAux.y) << std::endl;
    }
    return pos;
}



void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(matrix);
    for (unsigned int i= 0; i < npcs.size(); ++i) {
        if (npcs[i].isPrinted()) {
            const Npc* npc = &npcs[i];
            target.draw(*npc);
        }
    }
    target.draw(displais);

}

void Board::update(float deltaTime) {
    matrix.updateDraw(cameraPos);
    displais.update(deltaTime,cameraPos,npcs[0].getPosition());
    for (unsigned int i = 0; i < npcs.size(); ++i) {
        npcs[i].update(deltaTime,matrix);
    }

    // COLOCAR EN SU SITIO
    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;
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

void Board::updateCamera(float deltaTime, sf::Vector2f dir) {
    cameraPos = matrix.updateCamera(deltaTime,dir,cameraPos, cameraVel);
}

void Board::updateNpc(float deltaTime, sf::Vector2f dir) {
    sf::Vector2f pos = calculateColision(npcs[0], 1, dir);
    if (pos.x < 0) pos.x = 0;
    else if(pos.x >= COLS) pos.x = COLS;
    if (pos.y < 0) pos.y = 0;
    else if(pos.y >= ROWS) pos.y = ROWS;

    npcs[0].setMatPosition(pos);
}


