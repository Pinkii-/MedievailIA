#include "Textures.hpp"

sf::Font Textures::font;
sf::Texture Textures::none;
sf::Texture Textures::rock;
sf::Texture Textures::npc;
sf::Texture Textures::star;

void Textures::load()
{
	font.loadFromFile("Resources/helvetica.ttf");
	none.loadFromFile("Resources/pruebaTileBlanco.png");
	rock.loadFromFile("Resources/pruebaTile2.png");
	npc.loadFromFile("Resources/npc.png");
	star.loadFromFile("Resources/star.png");
}
