#include "display.h"
#include <string>
#include <sstream>

Display::Display()
{
}

void Display::init() {
    font.loadFromFile("Resources/helvetica.ttf");
    sf::Font *aux = &font;
    textos = std::vector<sf::Text> (nTextos);
    for (unsigned int i = 0; i < textos.size();++i) {
        textos[i].setFont(*aux);
        textos[i].setCharacterSize(25);
        textos[i].setColor(sf::Color::Blue);
        textos[i].setStyle(sf::Text::Bold);
    }

    textos[0].setPosition(sf::Vector2f(50,30));
    textos[1].setPosition(sf::Vector2f(50,55));
    textos[2].setPosition(sf::Vector2f(50,80));

    fps = 0;


}

void Display::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < textos.size(); ++i) {
        const sf::Text *aux = &textos[i];
        target.draw(*aux);
    }
}

void Display::update(float deltaTime, sf::Vector2f cameraPos, sf::Vector2f npc) {
    fps = fps*0.90 + (1.0/deltaTime)*0.1;
    std::string sAux = to_string(fps);
    textos[0].setString(sAux);
    textos[1].setString(to_string(cameraPos.x) + " " + to_string(cameraPos.y));
    textos[2].setString(to_string(npc.x) + " " + to_string(npc.y));
}

std::string Display::to_string(float x) {
    std::ostringstream buff;
    buff.precision(4);
    buff<<x;
    return buff.str();
}
