#include <iostream>
#include <fstream>

#include "Utils/util.h"
#include "map.h"


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    int sizei = matrix.size();
    int sizej = matrix[0].size();
    for (int i = 0; i < sizei; ++i) {
        for (int j = 0; j < sizej; ++j) {
            const Tile* tile = &matrix[i][j];
            target.draw(*tile);
        }

    }
}


Map::Map() {}


Map::Map(int cols, int rows) {
    matrix = std::vector<std::vector<Terrain> > (cols, (std::vector<Terrain> (rows)));
}

void Map::generateMap() {
    ////    TODO a random creator of maps
    if (GENERATE_MAP) {
        for (unsigned int i = 0; i < matrix.size(); ++i) {
            for (unsigned int j = 0; j < matrix[0].size(); ++j) {
                Land p;
                if (i == 0 or j == 0 or i == matrix.size()-1 or j == matrix[0].size() -1) p = Rock;
                else p = None;
                matrix[i][j] = Terrain(p,TILE_SIZE);
            }
        }
        int islands = 25;
        for (int i = 0; i < islands; ++i) {
            int x = std::rand() % COLS;
            int y = std::rand() % ROWS;
            if (isWalkeable(sf::Vector2f(x,y))) {
                for (int a = -1; a < 2; ++a) {
                    for (int b = -1; b < 2; ++b) {
                        matrix[x+a][y+b] = Terrain(Rock,TILE_SIZE);
                    }
                }
            }
            else --i;
        }
    }
    else loadMap();
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
        Land typo;
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
        matrix[j][i] = Terrain(typo,TILE_SIZE);
        //		if ((i+j)%2 == 0) matrix[j][i].setColor(sf::Color::Green);
        //		else matrix[j][i].setColor(sf::Color::Yellow);
        ++j;
        if (j >= matrix[0].size()) {
            j = 0;
            ++i;
        }

    }
    myfile.close();
}

void Map::initDraw() {
    int sizei = matrix.size();
    int sizej = matrix[0].size();
    for (int i = 0; i < sizei; ++i) {
        for (int j = 0; j < sizej; ++j) {
            sf::Vector2f position;
            position.x = TILE_SIZE*(float(i+UISPACE));
            position.y = TILE_SIZE*(float(j));
            matrix[i][j].setPosition(position);
        }
    }
}

bool Map::isWalkeable(sf::Vector2f pos) {
    int x = pos.x;
    int y = pos.y;

    if (x >= COLS or y >= ROWS or x < 0 or y < 0) return false;

    if (matrix[x][y].getLand() == None) return true;
    else return false;
}

sf::Vector2i Map::getSize() {
    sf::Vector2i aux;
    aux.x = matrix.size();
    aux.y = matrix[0].size();
    return aux;
}

Terrain Map::getTerrain(int x, int y) {
    return matrix[x][y];

}
