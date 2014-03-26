#include <string>
#include <sstream>

#include "Npcdisplayer.hpp"

void NpcDisplayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    target.draw(s);
    for (unsigned int i = 0; i < nTextosNpcDisplayer; ++i) {
        const sf::Text *aux = &texts[i];
        target.draw(*aux);
    }
}

NpcDisplayer::NpcDisplayer(): height(100),width(UISPACE*TILE_SIZE) {
}


NpcDisplayer::NpcDisplayer(int position, Npc* npc): n(npc),height(100),width(UISPACE*TILE_SIZE-10) {
    int x = 10;
    int y = 5;


    s = sf::RectangleShape(sf::Vector2f(width-x,height-y));
    s.setOutlineColor(sf::Color::Black);
    s.setOutlineThickness(1);
    sf::FloatRect textRect = s.getLocalBounds();
    s.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    s.setPosition((textRect.width+x)/2.f,(y+textRect.height/2.f)*(1+position*2));
    s.setFillColor(sf::Color::Cyan);

    int xtext = textRect.left + 20;
    int ytext = (y+textRect.height/2.f)*(position*2) + 20;
    texts = std::vector<sf::Text> (nTextosNpcDisplayer);
    for (unsigned int i = 0; i < nTextosNpcDisplayer; ++i) {
        texts[i].setFont(Textures::font);
        texts[i].setCharacterSize(15);
        texts[i].setColor(sf::Color::Black);
        texts[i].setPosition(sf::Vector2f(xtext,ytext));
        ytext += 20;
    }
}

void NpcDisplayer::update(){
    texts[0].setString("Rango maximo: " + std::to_string(n->getMaxDistance()));
    texts[1].setString("Objetivo actual: " + resourceToString(n->getPreference()));
}

bool NpcDisplayer::isClicked(sf::Vector2f pos){
    if (std::abs(pos.x - (s.getPosition().x)) < width and std::abs(pos.y - s.getPosition().y) < height) return true;
    else return false;
}

Npc* NpcDisplayer::getNpc() {
    return n;
}
