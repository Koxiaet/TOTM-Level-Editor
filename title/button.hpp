#include <SFML/Graphics.hpp>
#include <string>

#ifndef __KAI__TOTM__BUTTON__
#define __KAI__TOTM__BUTTON__ 1

#define key(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)
#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

class button
{
protected:
	sf::RectangleShape background;
	sf::Font& font;
	sf::Text text;
	sf::RectangleShape sides;

	int x;
	int y;
	uint w;

	bool hover;
public:
	button(sf::Font& _font);

	std::string str;

	void setPosition(int _x, int _y);
	void setWidth(uint _w);

	void draw(sf::RenderWindow& window);
	bool isClicked();
	void resetHover();
};

#endif