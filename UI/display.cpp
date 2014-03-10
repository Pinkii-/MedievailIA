#include "display.h"
#include <string>
#include <sstream>
#include "Utils/util.h"

std::string Display::to_string(float x,int precision) {
    std::ostringstream buff;
    buff.precision(precision);
    buff<<x;
    return buff.str();
}

void Display::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < nTextos; ++i) {
        const sf::Text *aux = &textos[i];
        target.draw(*aux);
    }
}


Display::Display()
{
}

void Display::init() {
	int x = WIDTH - 230;
	int y = 30;
    textos = std::vector<sf::Text> (nTextos);
    for (unsigned int i = 0; i < nTextos;++i) {
        textos[i].setFont(Textures::font);
        textos[i].setCharacterSize(25);
        textos[i].setColor(sf::Color::Blue);
        textos[i].setStyle(sf::Text::Bold);
		textos[i].setPosition(sf::Vector2f(x,y));
		y += 25;
	}
    fps = 0;
    updates = 0;

}

void Display::update(float deltaDraw, float deltaTime, sf::Vector2f cameraPos, sf::Vector2f npc) {
    fps = fps*0.90 + (1.0/deltaDraw)*0.1;
    updates = updates*0.90 + (1.0/deltaTime)*0.1;
    std::string sAux = to_string(fps,3);
    textos[0].setString("Fps " + sAux);
	textos[1].setString("Updates: " + to_string(updates,6));
    textos[2].setString(to_string(cameraPos.x,3) + " " + to_string(cameraPos.y,3));
    textos[3].setString(to_string(npc.x,3) + " " + to_string(npc.y,3));
}
