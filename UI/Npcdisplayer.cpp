#include "Npcdisplayer.hpp"

void NpcDisplayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(s);
}

NpcDisplayer::NpcDisplayer(): width(UISPACE*TILE_SIZE),height(100)
{
}

NpcDisplayer::NpcDisplayer(int position,Npc* npc): width(UISPACE*TILE_SIZE),height(100),n(npc)
{
    s = sf::RectangleShape(sf::Vector2f(width-10,height-10));
    sf::FloatRect textRect = s.getLocalBounds();
    s.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    s.setPosition((textRect.width+10)/2.f,((10+textRect.height/2.f))*(1+position));
    s.setFillColor(sf::Color::Cyan);
}


bool NpcDisplayer::isClicked(sf::Vector2f pos){
    if (std::abs(pos.x - (s.getPosition().x)) < width and std::abs(pos.y - s.getPosition().y) < height) return true;
    else return false;
}
