#include <SFML/Graphics.hpp>
#include "../colors.hpp"

#ifndef __KAI__TOTM__STAR__
#define __KAI__TOTM__STAR__ 1

class star
{
protected:
	sf::RectangleShape rect;

	uint x;
	uint y;
	uint starTimer;
public:
	star();
	star(uint maxx, uint maxy);
	void create(uint maxx, uint maxy);
	void draw(sf::RenderWindow& window);
};

#endif