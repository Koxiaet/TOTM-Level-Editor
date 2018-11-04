#include "menuSection.hpp"

menuSection::menuSection(): menuOpen(false), isHovering(false) {}

menuSection::menuSection(std::string _name): name(_name), menuOpen(false), isHovering(false) {}

std::string menuSection::getClicked()
{
	std::string result = "";
	for (size_t i = 0; i < items.size(); i++) {
		items[i].getClicked();
		if (items[i].clicked == true) {
			result = name + "->" + items[i].name;
		}
	}
	return result;
}

void menuSection::draw(sf::RenderWindow& window, uint& offset, const uint spacing, const uint padding, sf::Text& text, sf::RectangleShape& highlight)
{
	text.setString(name);
	text.setPosition(offset + spacing, padding);

	highlight.setPosition(text.getGlobalBounds().left - spacing, text.getGlobalBounds().top - padding);
	highlight.setSize(sf::Vector2f(text.getGlobalBounds().width + 2*spacing, text.getGlobalBounds().height + 2*padding));

	if (menuOpen) {
		window.draw(highlight);
		text.setFillColor(COL_NONE);
	} else {
		text.setFillColor(COL_MED);
	}
	window.draw(text);
	offset += text.getGlobalBounds().width;
	offset += spacing*2;

	if (menuOpen) {
		uint currentHeight = 0;
		uint currentWidth  = 0;
		const uint loffset = highlight.getGlobalBounds().left;
		const uint toffset = highlight.getGlobalBounds().height;
		const uint hpadding = 4;
		const uint vpadding = 4;

		for (size_t i = 0; i < items.size(); i++) {
			items[i].getDimsName(currentWidth, currentHeight, vpadding, text);	
		}
		sf::RectangleShape bkg;
		bkg.setFillColor(COL_NONE);
		bkg.setPosition(loffset, toffset);
		bkg.setSize(sf::Vector2f(currentWidth + 2*hpadding, currentHeight));
		window.draw(bkg);
		currentHeight = 0;
		for (size_t i = 0; i < items.size(); i++) {
			items[i].drawName(window, loffset, currentWidth, hpadding, toffset, currentHeight, vpadding, highlight, text);	
		}
	} else {
		for (size_t i = 0; i < items.size(); i++) {
			items[i].isHovering = false;	
		}
	}

	if (highlight.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		isHovering = true;
	} else {
		isHovering = false;
	}
}