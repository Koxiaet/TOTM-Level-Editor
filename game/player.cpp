#include "player.hpp"
#include "soundGenerator.hpp"

#include <climits>
#include <cmath>

// double ease(double time, double start, double change, double duration)
// {
// 	time /= duration/2.0;
// 	if (time < 1.0) {
// 		return change/2.0*time*time + start;
// 	}
// 	time--;
// 	return -change/2.0*(time*(time-2.0) - 1.0) + start;
// }

double ease(double time, double start, double change, double duration)
{
	time /= duration;
	return change*time*time + start;
}

void player::construct()
{
	loadSound();

	trail.setFillColor(COL_MED);
}

player::player(): 
	x(0),
	y(0),
	startx(0),
	starty(0),
	tempx(16),
	tempy(16),
	facing(down), 
	coins(0),
	animationCycle(0),
	traillength(0)
{
	construct();
}

player::player(size_t x, size_t y, direction facing):
	x(x),
	y(y),
	oldx(x),
	oldy(y),
	startx(x),
	starty(y),
	tempx(x*32+16),
	tempy(y*32+16),
	facing(facing),
	coins(0),
	animationCycle(0),
	traillength(0)
{
	construct();
}

void player::teleport(size_t _x, size_t _y, direction _facing, bool resetCoins)
{
	x      = _x;
	y      = _y;
	oldx   = x;
	oldy   = y;
	startx = x;
	starty = y;
	tempx  = x*32+16;
	tempy  = y*32+16;
	facing = _facing;
	if (resetCoins) {
		coins = 0;
	}
}

void player::kill()
{
	x      = startx;
	y      = starty;
	oldx   = x;
	oldy   = y;
	tempx  = x*32+16;
	tempy  = y*32+16;
	facing = down;
	coins  = 0;
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

sf::Vector2f player::getScroll()
{
	if (tempx == x*32+16 && tempy == y*32+16) {
		return sf::Vector2f(tempx, tempy);
	}


	sf::Vector2f r;
	if (facing == up) {
		r.x = tempx;
		double start         = (double)oldy*32+16;
		double current       = (double)tempy;
		double end           = (double)y*32+16;
		double currentChange = - abs(start - current);
		double totalChange   = - abs(start - end);
		r.y = ease(currentChange/32, start, totalChange, totalChange/32);
	} else if (facing == down) {
		r.x = tempx;
		double start         = (double)oldy*32+16;
		double current       = (double)tempy;
		double end           = (double)y*32+16;
		double currentChange = abs(start - current);
		double totalChange   = abs(start - end);
		r.y = ease(currentChange/32, start, totalChange, totalChange/32);
	} else if (facing == left) {
		r.y = tempy;
		double start         = (double)oldx*32+16;
		double current       = (double)tempx;
		double end           = (double)x*32+16;
		double currentChange = - abs(start - current);
		double totalChange   = - abs(start - end);
		r.x = ease(currentChange/32, start, totalChange, totalChange/32);
	} else if (facing == right) {
		r.y = tempy;
		double start         = (double)oldx*32+16;
		double current       = (double)tempx;
		double end           = (double)x*32+16;
		double currentChange = abs(start - current);
		double totalChange   = abs(start - end);
		r.x = ease(currentChange/32, start, totalChange, totalChange/32);
	}
	return r;
}

void player::draw(sf::RenderWindow& window, sf::Sprite& spr_player, sf::Sprite& spr_player_moving)
{
	if (tempx != x*32+16 || tempy != y*32+16) {
		if (facing == up) {
			traillength = oldy - ((tempy-16)/32);
		} else if (facing == down) {
			traillength = ((tempy-16)/32) - oldy;
		} else if (facing == left) {
			traillength = oldx - ((tempx-16)/32);
		} else if (facing == right) {
			traillength = ((tempx-16)/32) - oldx;
		}
		if (traillength < 0) {
			traillength = 0;
		}
		if (traillength > 5) {
			traillength = 5;
		}

		traillength *= 32;
	} else {
		if (traillength > 0) {
			traillength -= 32;
		}
	}

	if (facing == up) {
		trail.setPosition(tempx - 2, tempy);
		trail.setSize(sf::Vector2f(4, traillength));
		window.draw(trail);
		trail.setPosition(tempx - 6, tempy);
		trail.setSize(sf::Vector2f(2, traillength - 12));
		window.draw(trail);
		trail.setPosition(tempx + 4, tempy);
		trail.setSize(sf::Vector2f(2, traillength - 12));
		window.draw(trail);
	} else if (facing == down) {
		trail.setPosition(tempx - 2, tempy - traillength);
		trail.setSize(sf::Vector2f(4, traillength));
		window.draw(trail);
		trail.setPosition(tempx - 6, tempy - traillength + 12);
		trail.setSize(sf::Vector2f(2, traillength - 12));
		window.draw(trail);
		trail.setPosition(tempx + 4, tempy - traillength + 12);
		trail.setSize(sf::Vector2f(2, traillength - 12));
		window.draw(trail);
	} else if (facing == left) {
		trail.setPosition(tempx, tempy - 2);
		trail.setSize(sf::Vector2f(traillength, 4));
		window.draw(trail);
		trail.setPosition(tempx, tempy - 6);
		trail.setSize(sf::Vector2f(traillength - 12, 2));
		window.draw(trail);
		trail.setPosition(tempx, tempy + 4);
		trail.setSize(sf::Vector2f(traillength - 12, 2));
		window.draw(trail);
	} else if (facing == right) {
		trail.setPosition(tempx - traillength, tempy - 2);
		trail.setSize(sf::Vector2f(traillength, 4));
		window.draw(trail);
		trail.setPosition(tempx - traillength + 12, tempy - 6);
		trail.setSize(sf::Vector2f(traillength - 12, 2));
		window.draw(trail);
		trail.setPosition(tempx - traillength + 12, tempy + 4);
		trail.setSize(sf::Vector2f(traillength - 12, 2));
		window.draw(trail);
	}

	if (tempx == x*32+16 && tempy == y*32+16) {
		if (animationCycle == 0) {
			spr_player.setTextureRect(sf::IntRect(0, 0, 16, 16));
		} else if (animationCycle == 6) {
			spr_player.setTextureRect(sf::IntRect(16, 0, 16, 16));
		} else if (animationCycle == 12) {
			spr_player.setTextureRect(sf::IntRect(32, 0, 16, 16));
		} else if (animationCycle == 18) {
			spr_player.setTextureRect(sf::IntRect(48, 0, 16, 16));
		} else if (animationCycle == 24) {
			spr_player.setTextureRect(sf::IntRect(64, 0, 16, 16));
		} else if (animationCycle == 30) {
			spr_player.setTextureRect(sf::IntRect(64, 0, 16, 16));
		} else if (animationCycle == 36) {
			animationCycle = UINT_MAX; //overflow
		}
		animationCycle++;
		spr_player.setPosition(tempx, tempy);
			switch (facing) {
				case up:    spr_player.setRotation(180); break;
				case down:  spr_player.setRotation(0);   break;
				case left:  spr_player.setRotation(90);  break;
				case right: spr_player.setRotation(270); break;
			}
		window.draw(spr_player);
	} else {
		switch (facing) {
			case up:    spr_player_moving.setRotation(270);break;
			case down:  spr_player_moving.setRotation(90); break;
			case left:  spr_player_moving.setRotation(180);break;
			case right: spr_player_moving.setRotation(0);  break;
		}

		const int animDifference = 96;
		if (abs((int)oldx*32+16 - (int)tempx) >= animDifference*2 || abs((int)oldy*32+16 - (int)tempy) >= animDifference*2) {
			spr_player_moving.setTextureRect(sf::IntRect(32, 0, 16, 16));
		} else if (abs((int)oldx*32+16 - (int)tempx) >= animDifference || abs((int)oldy*32+16 - (int)tempy) >= animDifference) {
			spr_player_moving.setTextureRect(sf::IntRect(16, 0, 16, 16));
		} else if (abs((int)oldx*32+16 - (int)tempx) >= 0 || abs((int)oldy*32+16 - (int)tempy) >= 0) {
			spr_player_moving.setTextureRect(sf::IntRect(0, 0, 16, 16));
		}
		spr_player_moving.setPosition(tempx, tempy);
		window.draw(spr_player_moving);
	}
}