#include "menuItem.hpp"

#include <vector>

#ifndef __KAI__TOTM__MENUSECTION__
#define __KAI__TOTM__MENUSECTION__ 1

class menuSection
{
public:
	menuSection();
	menuSection(std::string _name);
	std::string name;
	std::vector<menuItem> items;
	bool menuOpen;
	bool isHovering;
	std::string getClicked();
	void draw(sf::RenderWindow& window, uint& offset, const uint spacing, const uint padding, sf::Text& text, sf::RectangleShape& highlight);
};

#endif