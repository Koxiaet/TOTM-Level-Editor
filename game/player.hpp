#include <cstddef>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Rect.hpp>

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
public:
	size_t x;
	size_t y;
	size_t startx;
	size_t starty;
	size_t tempx;
	size_t tempy;
	direction facing;
	uint recovering;
	uint coins;
	
	sf::SoundBuffer buf_death;
	sf::Sound       snd_death;

	player();
	player(size_t x, size_t y, direction facing);
	void teleport(size_t _x, size_t _y, direction _facing, bool resetCoins = false);
	void kill();
	void loadSound();
	sf::FloatRect getBounds();
};

#endif