#include "player.hpp"
#include "soundGenerator.hpp"

player::player(): x(0), y(0), startx(0), starty(0), tempx(16), tempy(16), facing(down), recovering(0), coins(0)
{
	loadSound();
}

player::player(size_t x, size_t y, direction facing):
	x(x),
	y(y),
	startx(x),
	starty(y),
	tempx(x*32+16),
	tempy(y*32+16),
	facing(facing),
	recovering(0),
	coins(0)
{
	loadSound();
}

void player::teleport(size_t _x, size_t _y, direction _facing, bool resetCoins)
{
	x = _x;
	y = _y;
	startx = x;
	starty = y;
	tempx = x*32+16;
	tempy = y*32+16;
	facing = _facing;
	if (resetCoins) {
		coins = 0;
	}
}

void player::kill()
{
	x          = startx;
	y          = starty;
	tempx      = x*32+16;
	tempy      = y*32+16;
	facing     = down;
	coins      = 0;
	//recovering = 1;
	snd_death.play();
}

void player::loadSound()
{
	buf_death = fallingSquareWave(1000, 100, 15, 3000);
	snd_death.setBuffer(buf_death);
	snd_death.setPosition(0,0,0);
	snd_death.setRelativeToListener(true);
}

sf::FloatRect player::getBounds()
{
	return sf::FloatRect(tempx - 16, tempy - 16, 32, 32);
}