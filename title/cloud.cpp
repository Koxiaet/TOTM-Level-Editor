#include "cloud.hpp"
#include "cstdlib"

cloud::cloud()
{
	if (rand()%2 == 0) {
		tex.loadFromFile("title/images/cloud1.png");
	} else {
		tex.loadFromFile("title/images/cloud2.png");
	}
	tex.setSmooth(false);
	spr.setTexture(tex);
	spr.setColor(COL_LOW);
	spr.setScale(4.0f, 4.0f);
}

cloud::cloud(uint _maxy): maxy(_maxy)
{
	if (rand()%2 == 0) {
		tex.loadFromFile("title/images/cloud1.png");
	} else {
		tex.loadFromFile("title/images/cloud2.png");
	}
	tex.setSmooth(false);
	spr.setTexture(tex);
	spr.setColor(COL_LOW);
	spr.setScale(4.0f, 4.0f);
	x = rand()%1200;
	y = rand()%maxy;
}

void cloud::create(uint _maxy)
{
	maxy = _maxy;
	x = rand()%1200;
	y = rand()%maxy;
}

void cloud::draw(sf::RenderWindow& window)
{
	if (x > (window.getSize().x + spr.getGlobalBounds().width)) {
		if (rand()%256 == 0) {
			x = 0;
			y = rand()%maxy;
		}
	}
	spr.setTexture(tex);

	while (y > (maxy - spr.getGlobalBounds().height)) {
		y--;
	}
	const uint speed = 1;
	x += speed;
	spr.setPosition(x - spr.getGlobalBounds().width, y);
	window.draw(spr);
}