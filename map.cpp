#include <iostream>
#include <fstream>

#include "map.h"
#include "util.h"



Map::Map() {}


Map::Map(int cols, int rows, std::vector<sf::Texture> *text) {
    matrix = std::vector<std::vector<Terrain> > (cols, (std::vector<Terrain> (rows)));
    props = std::vector<Prop> (0);
    texturas = *text;
}

void Map::generateMap() {
//    TODO a random creator of maps
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

void Map::generateProps() {
    //TODO a random generator of props on the map
    while (props.size() == 0) {
        int x,y;
        x = std::rand() % COLS;
        y = std::rand() % ROWS;
        if (isWalkeable(sf::Vector2f(x,y))) {
            sf::Texture *text = &texturas[tStar];
            Prop p = Prop(Star,text,sf::Vector2f(x,y),TILE_SIZE);
            props.push_back(p);
        }
    }
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



bool Map::isWalkeable(sf::Vector2f pos) {
    int x = pos.x;
    int y = pos.y;

    if (x >= ROWS or y >= COLS or x < 0 or y < 0) return false;

    if (matrix[x][y].getTypo() == None) return true;
    else return false;
}


//void Map::update(float deltaTime) {

//}


sf::Vector2f Map::updateCamera(float deltaTime, sf::Vector2f dir, sf::Vector2f cameraPos, sf::Vector2f cameraVel) {
    cameraPos.x += dir.x*cameraVel.x*deltaTime;
    cameraPos.y += dir.y*cameraVel.y*deltaTime;
    float sizex = WIDTH/TILE_SIZE;
    float sizey = HEIGHT/TILE_SIZE;
    if (cameraPos.x < 0) cameraPos.x = 0;
    else if(cameraPos.x >= COLS - sizex) cameraPos.x = COLS - sizex;
    if (cameraPos.y < 0) cameraPos.y = 0;
    else if(cameraPos.y >= ROWS - sizey) cameraPos.y = ROWS - sizey;
    return cameraPos;
}


void Map::updateDraw(sf::Vector2f cameraPos) {
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
//                if ((j + i)%2 == 0) matrix[i][j].setColor(sf::Color(125,125,125,255));
//                else matrix[i][j].setColor(sf::Color(0,255,0,255));
            }
            else matrix[i][j].setPrinted(false);
        }
    }

    for (unsigned int i= 0; i < props.size(); ++i) {
        sf::Vector2f posProp = props[i].getMatPosition();
        if (posProp.x >= cameraPos.x-1 and posProp.x < cameraPos.x + sizex + 1 and posProp.y >= cameraPos.y-1 and posProp.y < cameraPos.y+sizey+1) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(posProp.x-cameraPos.x);
            position.y = TILE_SIZE*(posProp.y-cameraPos.y);
            props[i].setPosition(position);
            props[i].setPrinted(true);
        }
        else props[i].setPrinted(false);
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
    for (unsigned int i= 0; i < props.size(); ++i) {
        if (props[i].isPrinted()) {
            const Prop* prop = &props[i];
            target.draw(*prop);
        }
    }
}
