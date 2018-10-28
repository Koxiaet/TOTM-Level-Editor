#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "panelItem.hpp"

#ifndef __KAI__TOTM__PANEL__
#define __KAI__TOTM__PANEL__ 1

#define key(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)
#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

class panel
{
protected:
	sf::RectangleShape bkg;
	sf::RectangleShape outline;
	sf::Font           fnt_totm;
	sf::Text           txt_label;
	sf::Vertex         selector[3];
public:
	std::vector<panelItem> items;
	uint selectedTileL;
	uint selectedTileR;
	panel();
	void draw(sf::RenderWindow& window);
};

#endif