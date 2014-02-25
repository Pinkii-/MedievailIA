#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Textures.hpp"

class Board;
class Interface : public sf::Drawable {
	private:
		Board* game;
		sf::RectangleShape fondo;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	public:
		Interface();
		void init(Board* g);
};

#endif // INTERFACE_HPP
