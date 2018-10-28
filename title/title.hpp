#include <SFML/Graphics.hpp>
#include <cstdint>

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
	sf::Texture tex_button;
	sf::Sprite  spr_button;
	sf::Texture tex_button_pressed;
	sf::Sprite  spr_button_pressed;

	sf::Texture tex_play;
	sf::Sprite  spr_play;

	sf::Texture tex_edit;
	sf::Sprite  spr_edit;

	sf::Texture tex_exit;
	sf::Sprite  spr_exit;

	sf::Font fnt_totm;
	sf::Text txt_name;
	sf::Text txt_sub;
public:
	title();
	uint testClicked(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

#endif