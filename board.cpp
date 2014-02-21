#include "board.h"
#include "map.cpp"

Board::Board()
{
}

void Board::init() {
    cameraPos = sf::Vector2f(0.0,0.0);
	cameraVel = 300;
    texturas = std::vector<sf::Texture> (NTEXTURES);
    loadTextures();
    // creacion de estructuras de datos
    matrix = Map(COLS,ROWS, &texturas);
    control = Control(&texturas);
	// inicializaciones de estructuras de datos
    matrix.generateMap();
    control.npcInit();
    displais.init();
    updateCamera(0,sf::Vector2f(0,0)); //despues de dibujar todo
}

void Board::loadTextures() {
    //Terrain Textures
	texturas[tNone].loadFromFile("Resources/pruebaTileBlanco.png");
    texturas[tRock].loadFromFile("Resources/pruebaTile2.png");

    //NPC Textures
    texturas[tNpc].loadFromFile("Resources/npc.png");

    //PROP Textures
    texturas[tStar].loadFromFile("Resources/star.png");
}


//sf::Vector2f Board::calculateColision(Npc n, float dt, sf::Vector2f dir) {

//    /* This shit should work, but by now it doesnt. So let's try to not look at it (/-_-)/ */

//    sf::Vector2f pos = n.getMatPosition();
//    float speed = n.getSpeed();
//    pos.x += dir.x*speed*dt;
//    pos.y += dir.y*speed*dt;

//    bool MatPos= false;
//    const sf::Vector2f constposAux = n.getMatPosition();
//    sf::Vector2f posAux = constposAux;
//    float hbMaxX = n.getHitBox().maxX/float(TILE_SIZE);
//    float hbMinX = n.getHitBox().minX/float(TILE_SIZE);
//    float hbMaxY = n.getHitBox().maxY/float(TILE_SIZE);
//    float hbMinY = n.getHitBox().minY/float(TILE_SIZE);
////    std::cout << std::end;
////    std::cout << "x: " << n.getMatPosition().x * TILE_SIZE << " y: " << n.getMatPosition().y * TILE_SIZE<< std::endl;
////    std::cout << "X: " << pos.x * TILE_SIZE                << " Y: " << pos.y * TILE_SIZE               << std::endl;
//    if (dir.x == 1) {
//        posAux.x += hbMaxX;
//        posAux.y += hbMaxY;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        posAux.y = constposAux.y + hbMinY;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        if(MatPos) pos.x = int(n.getMatPosition().x) + 1 - hbMaxX;
////        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " xs " << posAux.x << " " << int(posAux.x) << std::endl;
//    }
//    posAux = constposAux;
//    if (dir.x == -1) {
//        posAux.x += hbMinX;
//        posAux.y += hbMaxY;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        posAux.y = constposAux.y + hbMinY;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        if(MatPos) pos.x = int(n.getMatPosition().x) + 1 - hbMinX;
////        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " xs " << posAux.x << " " << int(posAux.x) << std::endl;
//    }
//    posAux = constposAux;
//    if (dir.y == 1) {
//        posAux.y += hbMaxY;
//        posAux.x += hbMaxX;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        posAux.x = constposAux.x + hbMinX;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        if(MatPos) pos.y = int(n.getMatPosition().y) + 1 - hbMaxY;
////        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " ys " << posAux.y << " " << int(posAux.y) << std::endl;
//    }
//    posAux = constposAux;
//    if (dir.y == -1) {
//        posAux.y += hbMinY;
//        posAux.x += hbMaxX;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        posAux.x = constposAux.x + hbMinX;
//        if (!matrix.isWalkeable(posAux)) MatPos = true;
//        if(MatPos) pos.y = int(n.getMatPosition().y) + 1 - hbMinY;
////        std::cout << "x: " << pos.x * TILE_SIZE << " y: " << pos.y * TILE_SIZE << " ys " << posAux.y << " " << int(posAux.y) << std::endl;
//    }
//    return pos;
//}



void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(matrix);
    target.draw(displais);
    target.draw(control);
}

void Board::update(float deltaTime) {
    matrix.updateDraw(cameraPos);
    control.update(deltaTime,matrix);
    control.updateDraw(cameraPos);
}

void Board::updateD(float deltaTime,float deltaDraw) {
    displais.update(deltaDraw,deltaTime,cameraPos,control.getNpc(0).getMatPosition());
}


void Board::updateCamera(float deltaTime, sf::Vector2f dir) {
    cameraPos = matrix.updateCamera(deltaTime,dir,cameraPos, cameraVel);
    control.updateDraw(cameraPos);
}




