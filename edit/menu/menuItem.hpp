#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef __KAI__TOTM__MENUITEM__
#define __KAI__TOTM__MENUITEM__ 1

class menuItem
{
public:
	std::string name;
	bool isHovering;
	std::vector<sf::Keyboard::Key> shortcut;
	bool clicked;
	menuItem();
	menuItem(std::string _name);
	void getDimsName(uint& currentWidth, uint& currentHeight, const uint vpadding, sf::Text& text);
	void getDimsShortcut(uint& currentWidth, uint& currentHeight, const uint vpadding, sf::Text& text);
	void getClicked();
	void drawName(
		sf::RenderWindow& window,
		const uint loffset,
		const uint width,
		const uint hpadding,
		const uint toffset,
		uint& currentHeight,
		const uint vpadding,
		sf::RectangleShape highlight,
		sf::Text& text
	);
};

#endif