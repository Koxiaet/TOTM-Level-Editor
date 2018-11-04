#include "../colors.hpp"
#include <SFML/Graphics.hpp>

#ifndef __KAI__TOTM__CLOUD__
#define __KAI__TOTM__CLOUD__ 1

class cloud
{
protected:
	sf::Texture tex;
	sf::Sprite  spr;

	uint x;
	uint y;
public:
	cloud();
	cloud(uint _maxy);
	void create(uint _maxy);
	uint maxy;
	void draw(sf::RenderWindow& window);
};

#endif