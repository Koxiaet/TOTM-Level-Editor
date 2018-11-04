#include "button.hpp"
#include "../colors.hpp"

button::button(sf::Font& _font): font(_font), hover(false)
{
	background.setFillColor(COL_MED);
	sides.setFillColor(COL_MED);
	sides.setSize(sf::Vector2f(4, 56));

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(COL_NONE);
}

void button::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

void button::setWidth(uint _w)
{
	w = _w;
}

void button::draw(sf::RenderWindow& window)
{
	background.setSize(sf::Vector2f(w - 16, 56));
	background.setPosition(x + 8, y);

	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width/2, 0);

	if (background.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		background.setPosition(x + 8, y + 8);
		sides.setPosition(x, y + 8);
		window.draw(sides);
		sides.setPosition(x + 4, y + 8);
		window.draw(sides);
		sides.setPosition(x + w - 4, y + 8);
		window.draw(sides);
		sides.setPosition(x + w - 8, y + 8);
		window.draw(sides);

		text.setPosition(x + w/2, y + 36);

		hover = true;
	} else {
		sides.setPosition(x, y + 8);
		window.draw(sides);
		sides.setPosition(x + 4, y + 4);
		window.draw(sides);
		sides.setPosition(x + w - 4, y + 8);
		window.draw(sides);
		sides.setPosition(x + w - 8, y + 4);
		window.draw(sides);

		text.setPosition(x + w/2, y + 28);

		hover = false;
	}
	window.draw(background);
	window.draw(text);
}

bool button::isClicked()
{
	if (hover && mouse(Left)) {
		return true;
	}
	return false;
}

void button::resetHover()
{
	hover = false;
}