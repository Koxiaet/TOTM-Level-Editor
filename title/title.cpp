#include "title.hpp"

title::title()
{
	tex_button.loadFromFile("images/button.png");
	tex_button.setSmooth(false);
	spr_button.setTexture(tex_button);
	spr_button.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_button.setOrigin(8, 8);

	tex_button_pressed.loadFromFile("images/button_pressed.png");
	tex_button_pressed.setSmooth(false);
	spr_button_pressed.setTexture(tex_button_pressed);
	spr_button_pressed.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_button_pressed.setOrigin(8, 8);

	tex_edit.loadFromFile("title/images/editButton.png");
	tex_edit.setSmooth(false);
	spr_edit.setTexture(tex_edit);
	spr_edit.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_edit.setOrigin(8, 8);

	tex_play.loadFromFile("title/images/playButton.png");
	tex_play.setSmooth(false);
	spr_play.setTexture(tex_play);
	spr_play.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_play.setOrigin(8, 8);

	tex_exit.loadFromFile("title/images/exitButton.png");
	tex_exit.setSmooth(false);
	spr_exit.setTexture(tex_exit);
	spr_exit.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_exit.setOrigin(8, 8);

	fnt_totm.loadFromFile("totm.ttf");

	txt_name.setFont(fnt_totm);
	txt_name.setCharacterSize(40);
	txt_name.setString("TOMB OF THE MASK");
	txt_name.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
	txt_name.setOrigin(txt_name.getGlobalBounds().width/2, 0);

	txt_sub.setFont(fnt_totm);
	txt_sub.setCharacterSize(20);
	txt_sub.setString("LEVEL CREATOR");
	txt_sub.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
	txt_sub.setOrigin(txt_sub.getGlobalBounds().width/2, 0);
}

uint title::testClicked(sf::RenderWindow& window) //0 for none, 1 for play, 2 for edit, 3 for exit
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (spr_play.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
			return playButton;
		}
		if (spr_edit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
			return editButton;
		}
		if (spr_exit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
			return exitButton;
		}
	}
	// if (key(Escape)) {
	// 	return exitButton;
	// }
	return noButton;
}

void title::draw(sf::RenderWindow& window)
{
	window.setTitle("Tomb of the Mask");
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
	txt_name.setPosition(window.getSize().x/2, 20);
	window.draw(txt_name);
	txt_sub.setPosition(window.getSize().x/2, txt_name.getGlobalBounds().height + 30);
	window.draw(txt_sub);

	spr_edit.setPosition(window.getSize().x/2-128, window.getSize().y/2);
	spr_play.setPosition(window.getSize().x/2,     window.getSize().y/2);
	spr_exit.setPosition(window.getSize().x/2+128, window.getSize().y/2);

	if (spr_edit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
		spr_button_pressed.setPosition(spr_edit.getPosition());
		spr_edit.move(0, 8);
		window.draw(spr_button_pressed);
	} else {
		spr_button.setPosition(spr_edit.getPosition());
		window.draw(spr_button);
	}

	if (spr_play.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
		spr_button_pressed.setPosition(spr_play.getPosition());
		spr_play.move(0, 8);
		window.draw(spr_button_pressed);
	} else {
		spr_button.setPosition(spr_play.getPosition());
		window.draw(spr_button);
	}

	if (spr_exit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
		spr_button_pressed.setPosition(spr_exit.getPosition());
		spr_exit.move(0, 8);
		window.draw(spr_button_pressed);
	} else {
		spr_button.setPosition(spr_exit.getPosition());
		window.draw(spr_button);
	}

	window.draw(spr_edit);
	window.draw(spr_play);
	window.draw(spr_exit);
}