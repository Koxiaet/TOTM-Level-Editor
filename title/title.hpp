#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include "../colors.hpp"
#include "button.hpp"
#include "cloud.hpp"
#include "star.hpp"

#ifndef __KAI__TOTM__TITLE__
#define __KAI__TOTM__TITLE__ 1

#define key(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)

enum buttonClicked: uint8_t
{
	noButton = 0,
	editButton = 1,
	playButton = 2,
	exitButton = 3
};

class title
{
protected:
	sf::Texture tex_background;
	sf::Sprite  spr_background;
	sf::Sprite  spr_tower;

	button but_play;
	button but_edit;
	button but_exit;

	sf::Texture tex_title;
	sf::Sprite  spr_title;

	sf::Font fnt_totm;
	sf::Text txt_sub;

	sf::RectangleShape sea;
	uint seaTimer;
	unsigned long oldSeed;

	star*  stars;
	const size_t starLength = 20;
	cloud* clouds;
	const size_t cloudLength = 5;
public:
	title();
	uint testClicked();
	void draw(sf::RenderWindow& window);
	void resize(sf::RenderWindow& window);
	~title();
};

#endif