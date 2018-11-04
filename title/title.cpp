#include "title.hpp"
#include "../rand.hpp"
#include <iostream>
#include <cmath>

title::title(): but_play(fnt_totm), but_edit(fnt_totm), but_exit(fnt_totm), seaTimer(0)
{
	tex_background.loadFromFile("title/images/background.png");
	tex_background.setSmooth(false);
	spr_background.setTexture(tex_background);
	spr_background.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_background.setOrigin(tex_background.getSize().x/2, 0);
	spr_background.setColor(COL_LOW);
	spr_tower.setTexture(tex_background);
	spr_tower.setTextureRect(sf::IntRect(0, 0, tex_background.getSize().x, 1));
	spr_tower.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_tower.setOrigin(tex_background.getSize().x/2, 0);
	spr_tower.setColor(COL_LOW);

	tex_title.loadFromFile("title/images/logo.png");
	tex_title.setSmooth(false);
	spr_title.setTexture(tex_title);
	spr_title.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_title.setOrigin(tex_title.getSize().x/2, 0);
	spr_title.setColor(COL_MED);

	fnt_totm.loadFromFile("totm.ttf");

	but_play.str = "p";
	but_edit.str = "e";
	but_exit.str = "x";

	txt_sub.setFont(fnt_totm);
	txt_sub.setCharacterSize(20);
	txt_sub.setString("LEVEL CREATOR");
	txt_sub.setFillColor(COL_MED);
	txt_sub.setOrigin(txt_sub.getGlobalBounds().width/2, 0);

	sea.setFillColor(COL_LOW);
	sea.setSize(sf::Vector2f(8, 4));

	oldSeed = r.getseed();

	clouds = new cloud[cloudLength];
	for (size_t i = 0; i < cloudLength; i++) {
		clouds[i].create(300);
	}

	stars = new star[starLength];
	for (size_t i = 0; i < starLength; i++) {
		stars[i].create(800, 300 + 64 + 22*4);
	}
}

uint title::testClicked() //0 for none, 1 for play, 2 for edit, 3 for exit
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (but_play.isClicked()) {
			return playButton;
		}
		if (but_edit.isClicked()) {
			return editButton;
		}
		if (but_exit.isClicked()) {
			return exitButton;
		}
	}
	return noButton;
}

void title::draw(sf::RenderWindow& window)
{
	window.setTitle("Tomb of the Mask");
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	for (size_t i = 0; i < starLength; i++) {
		stars[i].draw(window);
	}

	for (size_t i = 0; i < cloudLength; i++) { //0 to 7 inclusive clouds
		clouds[i].maxy = window.getSize().y/2;
		clouds[i].draw(window);
	}

	for (uint i = 0; i < (window.getSize().y/2 + 64)/4 + 1; i++) {
		spr_tower.setPosition(window.getSize().x/2, i*4);
		window.draw(spr_tower);
	}

	spr_background.setPosition(window.getSize().x/2, window.getSize().y/2 + 64);
	window.draw(spr_background);

	spr_title.setPosition(window.getSize().x/2, 0);
	window.draw(spr_title);
	txt_sub.setPosition(window.getSize().x/2, (tex_title.getSize().y*4));
	window.draw(txt_sub);

	but_edit.setPosition(0, window.getSize().y - 64);
	but_edit.setWidth(64);
	but_play.setPosition(64, window.getSize().y - 64);
	but_play.setWidth(window.getSize().x - 128);
	but_exit.setPosition(window.getSize().x - 64, window.getSize().y - 64);
	but_exit.setWidth(64);

	but_edit.draw(window);
	but_play.draw(window);
	but_exit.draw(window);

	uint counter = 1;
	uint gap = 12;
	for (uint i = window.getSize().y/2 + 64 + 22*4; i < window.getSize().y-64; i += gap) {
		for (uint j = 0; j < window.getSize().x; j += 16) {
			if ((double)r.rand() / (double)r.rand_max < 1.0 / (1 + exp(0.5*(double)counter - 4))) {
				sea.setPosition(j, i);
				window.draw(sea);
			}
		}
		counter += 2;
		gap += 4;
	}

	if (seaTimer < 20) {
		r.reseed(oldSeed);
	} else {
		seaTimer = 0;
		oldSeed = r.getseed();
	}

	seaTimer++;
}

void title::resize(sf::RenderWindow& window)
{
	for (size_t i = 0; i < starLength; i++) {
		stars[i].create(window.getSize().x, window.getSize().y/2 + 64 + 22*4);
	}
}

title::~title()
{
	delete [] stars;
	delete [] clouds;
}