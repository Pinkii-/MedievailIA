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
    textos[3].setPosition(sf::Vector2f(50,110));

    fps = 0;
    updates = 0;

}

void Display::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < textos.size(); ++i) {
        const sf::Text *aux = &textos[i];
        target.draw(*aux);
    }
}

void Display::update(float deltaDraw, float deltaTime, sf::Vector2f cameraPos, sf::Vector2f npc) {
    fps = fps*0.90 + (1.0/deltaDraw)*0.1;
    updates = updates*0.90 + (1.0/deltaTime)*0.1;
    std::string sAux = to_string(fps,3);
    textos[0].setString("Fps " + sAux);
    textos[1].setString("Updates: " + to_string(updates,5));
    textos[2].setString(to_string(cameraPos.x,3) + " " + to_string(cameraPos.y,3));
    textos[3].setString(to_string(npc.x,3) + " " + to_string(npc.y,3));
}

std::string Display::to_string(float x,int precision) {
    std::ostringstream buff;
    buff.precision(precision);
    buff<<x;
    return buff.str();
}
