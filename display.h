#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#define nTextos 4

class Display : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<sf::Text> textos;
    sf::Font font;

    float fps,updates;

    std::string to_string(float x, int precision);

    sf::Text aux;

public:
    Display();
    void init();
    void update(float deltaDraw, float deltaTime, sf::Vector2f cameraPos, sf::Vector2f npc);

};

#endif // DISPLAY_H
