#include "panel.hpp"

panel::panel(): selectedTileL(3), selectedTileR(0)
{
	bkg.setPosition(0, 28);
	bkg.setFillColor(COL_NONE);

	outline.setFillColor(COL_TRANSPARENT);
	outline.setOutlineColor(COL_MED);
	outline.setOutlineThickness(2.0f);
	outline.setSize(sf::Vector2f(40, 40));
	outline.setOrigin(20, 20);

	fnt_totm.loadFromFile("totm.ttf");
	txt_label.setFont(fnt_totm);
	txt_label.setCharacterSize(15);
	txt_label.setFillColor(COL_MED);

	selector[0].color = COL_MED;
	selector[1].color = COL_MED;
	selector[2].color = COL_MED;
}

void panel::draw(sf::RenderWindow& window)
{
	const uint padding = 16;
	bool drawLabel = false;

	bkg.setSize(sf::Vector2f(32*4 + padding*5, window.getSize().y - 28));
	window.draw(bkg);

	for (size_t i = 0; i < items.size(); i++) {
		const int xpos = (i%4)*32 + (i%4 + 1)*padding + 16; //middle of the icon
		const int ypos = (i/4)*32 + (i/4 + 1)*padding + 16 + 28;
		outline.setPosition(xpos, ypos);
		window.draw(outline);
		if (items[i].sprite != NULL) {
			items[i].sprite->setPosition(xpos, ypos);
			window.draw(*(items[i].sprite));
		}

		const uint size = 20; //length of the sides of the right angled marker triangle

		if (selectedTileL == items[i].id) {
			//this is the one being selected. draw selector
			const int cornerx = xpos - 20;
			const int cornery = ypos + 20;
			selector[0].position = sf::Vector2f(cornerx, cornery - size);
			selector[1].position = sf::Vector2f(cornerx + size, cornery);
			selector[2].position = sf::Vector2f(cornerx, cornery);
			window.draw(selector, 3, sf::Triangles);
		}
		if (selectedTileR == items[i].id) {
			//this is the one being selected. draw selector
			const int cornerx = xpos + 20;
			const int cornery = ypos + 20;
			selector[0].position = sf::Vector2f(cornerx, cornery - size);
			selector[1].position = sf::Vector2f(cornerx - size, cornery);
			selector[2].position = sf::Vector2f(cornerx, cornery);
			window.draw(selector, 3, sf::Triangles);
		}

		if (outline.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			drawLabel = true;
			txt_label.setString(items[i].name);
			txt_label.setPosition(0, window.getSize().y - 20);
		}

		if (mouse(Left)) {
			if (outline.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				selectedTileL = items[i].id;
			}
		}
		if (mouse(Right)) {
			if (outline.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				selectedTileR = items[i].id;
			}
		}
	}

	if (drawLabel) {
		window.draw(txt_label);
	}
}