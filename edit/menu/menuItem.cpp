#include "menuItem.hpp"

#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

char getKeyChar(const sf::Keyboard::Key key)
{
	switch (key) {
		case sf::Keyboard::A:        return 'A';
		case sf::Keyboard::B:        return 'B';
		case sf::Keyboard::C:        return 'C';
		case sf::Keyboard::D:        return 'D';
		case sf::Keyboard::E:        return 'E';
		case sf::Keyboard::F:        return 'F';
		case sf::Keyboard::G:        return 'G';
		case sf::Keyboard::H:        return 'H';
		case sf::Keyboard::I:        return 'I';
		case sf::Keyboard::J:        return 'J';
		case sf::Keyboard::K:        return 'K';
		case sf::Keyboard::L:        return 'L';
		case sf::Keyboard::M:        return 'M';
		case sf::Keyboard::N:        return 'N';
		case sf::Keyboard::O:        return 'O';
		case sf::Keyboard::P:        return 'P';
		case sf::Keyboard::Q:        return 'Q';
		case sf::Keyboard::R:        return 'R';
		case sf::Keyboard::S:        return 'S';
		case sf::Keyboard::T:        return 'T';
		case sf::Keyboard::U:        return 'U';
		case sf::Keyboard::V:        return 'V';
		case sf::Keyboard::W:        return 'W';
		case sf::Keyboard::X:        return 'X';
		case sf::Keyboard::Y:        return 'Y';
		case sf::Keyboard::Z:        return 'Z';
		case sf::Keyboard::LShift:   return 'a';
		case sf::Keyboard::LControl: return 'b';
		case sf::Keyboard::LSystem:  return 'b';
		default:                     return '@';
	}
}

std::string getShortcutString(std::vector<sf::Keyboard::Key> shortcut)
{
	std::string result = "";
	for (size_t i = 0; i < shortcut.size(); i++) {
		if (i != 0) {
			result += "+";
		}
		result += getKeyChar(shortcut[i]);
	}
	return result;
}

menuItem::menuItem(): isHovering(false) {}
menuItem::menuItem(std::string _name): name(_name), isHovering(false) {}

void menuItem::getDimsName(uint& currentWidth, uint& currentHeight, const uint vpadding, sf::Text& text)
{
	text.setString(name + "  " + getShortcutString(shortcut));
	uint width = text.getGlobalBounds().width;
	if (width > currentWidth) {
		currentWidth = width;
	}

	uint height = text.getGlobalBounds().height;
	currentHeight += height + 2*vpadding;
}

void menuItem::getClicked()
{
	bool shortcutPressed = false;
	if (shortcut.size() > 0) {
		shortcutPressed = true;
		for (size_t i = 0; i < shortcut.size(); i++) {
			if (!sf::Keyboard::isKeyPressed(shortcut[i])) {
				shortcutPressed = false;
				break;
			}
		}
	}

	if ((mouse(Left) && isHovering) || (shortcutPressed)) {
		clicked = true;
	} else {
		clicked = false;
	}
}

void menuItem::drawName(
	sf::RenderWindow& window,
	const uint loffset,
	const uint width,
	const uint hpadding,
	const uint toffset,
	uint& currentHeight,
	const uint vpadding,
	sf::RectangleShape highlight,
	sf::Text& text
)
{
	text.setString(name + "  " + getShortcutString(shortcut));
	text.setPosition(loffset + hpadding, toffset + currentHeight + vpadding);

	highlight.setPosition(loffset, toffset + currentHeight);
	highlight.setSize(sf::Vector2f(width + 2*hpadding, text.getGlobalBounds().height + 2*vpadding));

	if (highlight.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		text.setFillColor(sf::Color(0, 0, 0));
		window.draw(highlight);
		isHovering = true;
	} else {
		text.setFillColor(sf::Color(0xFF, 0xFF, 00));
		isHovering = false;
	}

	window.draw(text);

	currentHeight += text.getGlobalBounds().height + 2*vpadding;
}