#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Utils/Textures.hpp"

class Board;
class Interface : public sf::Drawable {
	private:
		Board* game;
		sf::RectangleShape fondo;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		Interface();
		void init(Board* g);
        void update();
};

#endif // INTERFACE_HPP
