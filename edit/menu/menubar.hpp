#include "menuSection.hpp"

#ifndef __KAI__TOTM__MENUBAR__
#define __KAI__TOTM__MENUBAR__ 1

class menubar
{
protected:
	sf::Font totm;
	sf::Text text;
	sf::RectangleShape highlight;
	size_t menuOpen;
	bool oldMouseLeft;
public:
	std::vector<menuSection> items;
	std::string clicked;
	menubar();
	std::string getClicked();
	void draw(sf::RenderWindow& window);
};

#endif