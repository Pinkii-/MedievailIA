#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "SFML/Graphics.hpp"

class Textures
{
	public:
		static sf::Font font;
		static sf::Texture none;
		static sf::Texture rock;
		static sf::Texture npc;
		static sf::Texture star;
		static void load();
};

#endif // TEXTURES_HPP
