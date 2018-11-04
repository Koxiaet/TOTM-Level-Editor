#include <cstddef>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../colors.hpp"

#ifndef __KAI__TOTM__DIRECTION__
#define __KAI__TOTM__DIRECTION__ 1

enum directionEnum: uint8_t
{
	up = 0,
	down = 1,
	left = 2,
	right = 3
};

typedef uint8_t direction;

#endif

#ifndef __KAI__TOTM__PLAYER__
#define __KAI__TOTM__PLAYER__ 1

class player
{
protected:
	void construct();
public:
	size_t x;
	size_t y;
	size_t oldx;
	size_t oldy;
	size_t startx;
	size_t starty;
	size_t tempx;
	size_t tempy;
	direction facing;
	uint coins;
	uint animationCycle;
	int traillength;
	
	sf::SoundBuffer buf_death;
	sf::Sound       snd_death;

	sf::RectangleShape trail;

	player();
	player(size_t x, size_t y, direction facing);
	void teleport(size_t _x, size_t _y, direction _facing, bool resetCoins = false);
	void kill();
	void loadSound();
	sf::FloatRect getBounds();
	sf::Vector2f  getScroll();
	void draw(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& spr_player_moving);
};

#endif