#include "star.hpp"

star::star(): x(0), y(0), starTimer(20)
{
	rect.setFillColor(COL_LOW);
	starTimer = rand()%80;
}

star::star(uint maxx, uint maxy): starTimer(20)
{
	rect.setFillColor(COL_LOW);
	x = rand()%maxx;
	y = rand()%maxy;
	starTimer = rand()%80;
}

void star::create(uint maxx, uint maxy)
{
	x = rand()%maxx;
	y = rand()%maxy;
}

void star::draw(sf::RenderWindow& window)
{
	if (starTimer == 20) {
		rect.setSize(sf::Vector2f(4.0f, 4.0f));
		rect.setPosition(x, y);
		window.draw(rect);
		if (rand()%120 == 0) {
			starTimer = 0;
		}
	} else if (starTimer < 20) {
		rect.setSize(sf::Vector2f(12.0f, 4.0f));
		rect.setPosition(x - 4, y);
		window.draw(rect);

		rect.setSize(sf::Vector2f(4.0f, 12.0f));
		rect.setPosition(x, y - 4);
		window.draw(rect);
		starTimer++;
	}
}