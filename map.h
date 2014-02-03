#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>


template<class T>
class Map : public sf::Drawable
{
private:
    std::vector<std::vector<T> > matrix;
    std::vector<sf::Texture> texturas;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Map();
    Map(int cols, int rows,std::vector<sf::Texture> *text);
    void generateMap();
    void loadMap();
    bool isWalkeable(sf::Vector2f pos);

    void update(float deltaTime);
    sf::Vector2f updateCamera(float deltaTime, sf::Vector2f dir, sf::Vector2f cameraPos, sf::Vector2f cameraVel);
    void updateDraw(sf::Vector2f cameraPos);
};

#endif // MAP_H
