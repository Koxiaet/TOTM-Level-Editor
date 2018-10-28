#include "menubar.hpp"

#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

menubar::menubar(): menuOpen(SIZE_MAX), oldMouseLeft(false)
{
	totm.loadFromFile("totm.ttf");
	text.setFont(totm);
	text.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
	text.setCharacterSize(20);
	highlight.setFillColor(sf::Color(0xFF,0xFF,0));
}

void menubar::draw(sf::RenderWindow& window)
{
	const uint spacing = 16;
	const uint padding = 4;
	const uint loffset = 0;

	sf::RectangleShape barbkg;
	barbkg.setSize(sf::Vector2f(window.getSize().x - loffset, 20 + 2*padding));
	barbkg.setFillColor(sf::Color(0,0,0));
	barbkg.setPosition(loffset, 0);
	window.draw(barbkg);

	uint currentWidth = loffset;

	for (size_t i = 0; i < items.size(); i++) {
		items[i].draw(window, currentWidth, spacing, padding, text, highlight);
	}

	if (menuOpen == SIZE_MAX) {
		clicked = "";
	}

	for (size_t i = 0; i < items.size(); i++) {
		std::string getClicked = items[i].getClicked();
		if (getClicked != "") {
			clicked = getClicked;
			break;
		}
	}

	if (mouse(Left)) {
		if (!oldMouseLeft) {
			oldMouseLeft = true;
			if (menuOpen != SIZE_MAX) {
				menuOpen = SIZE_MAX;
			} else {
				for (size_t i = 0; i < items.size(); i++) {
					if (items[i].isHovering) {
						menuOpen = i;
						items[i].menuOpen = true;
					} else {
						items[i].menuOpen = false;
					}
				}
			}
		}
	} else {
		oldMouseLeft = false;
	}
	if (menuOpen != SIZE_MAX) {
		size_t oldMenuOpen = menuOpen;
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i].isHovering) {
				menuOpen = i;
				items[i].menuOpen = true;
			} else {
				items[i].menuOpen = false;
			}
		}
		if (menuOpen == oldMenuOpen) {
			items[menuOpen].menuOpen = true;
		}
	} else {
		for (size_t i = 0; i < items.size(); i++) {
			items[i].menuOpen = false;
		}
	}
}