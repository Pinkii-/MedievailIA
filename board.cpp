#include "board.h"
#include "map.cpp"


void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    target.draw(matrix);
	ui.drawBefore(target);
	target.draw(control);
	target.draw(ui);
    target.draw(displais);
}

Board::Board(sf::RenderWindow* window) : win(window) {
}

void Board::init() {
    cameraPos = sf::Vector2f(0.0,0.0);
    cameraVel = 10;
    cameraWait = 0;
    view = sf::View (sf::FloatRect(UISPACE*TILE_SIZE, 0, win->getSize().x-UISPACE*TILE_SIZE, win->getSize().y));
    win->setView(view);
    texturas.load();
    // creacion de estructuras de datos
    matrix = Map(COLS,ROWS);
    control = Control();
    // inicializaciones de estructuras de datos
    matrix.generateMap();
    control.init(&matrix);
    displais.init();
    ui.init(this);
    updateCamera(0); //despues de dibujar todo 
}

void Board::update(float deltaTime) {
    updateCamera(deltaTime);
    control.update(deltaTime,matrix);
}

void Board::updateD(float deltaTime,float deltaDraw) {
    matrix.initDraw();
    control.initDraw();
    ui.update();
    displais.update(deltaDraw,deltaTime,cameraPos);
}

void Board::updateCamera(float deltaTime) {
    if (cameraWait > 0) {
        cameraWait -= deltaTime;
        float distancia = cameraVel*deltaTime;
        cameraPos.x += cameraDir.x*distancia;
        cameraPos.y += cameraDir.y*distancia;
        float sizex = WIDTH/TILE_SIZE;
        float sizey = HEIGHT/TILE_SIZE;
        if (cameraPos.x < 0) cameraPos.x = 0;
        else if(cameraPos.x >= COLS - sizex + UISPACE) cameraPos.x = COLS - sizex + UISPACE;
        if (cameraPos.y < 0) cameraPos.y = 0;
        else if(cameraPos.y >= ROWS - sizey) cameraPos.y = ROWS - sizey;
        win->setView(sf::View(sf::FloatRect(UISPACE*TILE_SIZE+cameraPos.x*TILE_SIZE, cameraPos.y*TILE_SIZE, win->getSize().x-UISPACE*TILE_SIZE, win->getSize().y)));
    }
    control.initDraw();
}

void Board::updateDirCamera(sf::Vector2f d){
    cameraDir = d;
    cameraWait = 0.1;
}

void Board::onMouseButtonPressed(sf::Event event) {
    ui.isClicked(sf::Vector2f(event.mouseButton.x,event.mouseButton.y));
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

Control Board::getControl() {
    return control;
}
