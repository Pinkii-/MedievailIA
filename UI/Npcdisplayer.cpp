#include "Npcdisplayer.hpp"

void NpcDisplayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(s);
}

NpcDisplayer::NpcDisplayer(): width(UISPACE*TILE_SIZE),height(100) {
}

NpcDisplayer::NpcDisplayer(int position,Npc* npc): width(UISPACE*TILE_SIZE-10),height(100),n(npc) {
    int x = 10;
    int y = 5;
    s = sf::RectangleShape(sf::Vector2f(width-x,height-y));
    s.setOutlineColor(sf::Color::Black);
    s.setOutlineThickness(1);
    sf::FloatRect textRect = s.getLocalBounds();
    s.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    s.setPosition((textRect.width+x)/2.f,((y+textRect.height/2.f))*(1+position*2));
    s.setFillColor(sf::Color::Cyan);
}

void NpcDisplayer::update(){
}

bool NpcDisplayer::isClicked(sf::Vector2f pos){
    if (std::abs(pos.x - (s.getPosition().x)) < width and std::abs(pos.y - s.getPosition().y) < height) return true;
    else return false;
}

Npc* NpcDisplayer::getNpc() {
    return n;
}
