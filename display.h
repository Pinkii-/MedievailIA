#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Textures.hpp"

#define nTextos 4

class Display : public sf::Drawable
{
private:
    std::vector<sf::Text> textos;
    float fps,updates;
    std::string to_string(float x, int precision);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Display();
    void init();
    void update(float deltaDraw, float deltaTime, sf::Vector2f cameraPos, sf::Vector2f npc);
};

#endif // DISPLAY_H
