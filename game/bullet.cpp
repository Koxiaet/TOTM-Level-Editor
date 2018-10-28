#include "bullet.hpp"

bullet::bullet(): goalx(0), goaly(0), tempx(0), tempy(0), angle(0) {

}

bullet::bullet(const size_t _goalx, const size_t _goaly, const size_t _tempx, const size_t _tempy, const float _angle):
	goalx(_goalx),
	goaly(_goaly),
	tempx(_tempx),
	tempy(_tempy),
	angle(_angle)
{
	tempx = tempx*32 + 16;
	tempy = tempy*32 + 16;
}

bool bullet::draw(sf::RenderWindow& window, sf::Sprite& spr_bullet)
{
	const size_t speed = 16;
	if (tempx < goalx*32+16) { //right
		tempx += speed;
	}
	if (tempx > goalx*32+16) { //left
		tempx -= speed;
	}
	if (tempy < goaly*32+16) { //down
		tempy += speed;
	}
	if (tempy > goaly*32+16) { //up
		tempy -= speed;
	}
	spr_bullet.setRotation(angle);
	spr_bullet.setPosition(tempx, tempy);
	window.draw(spr_bullet);
	if (tempx == goalx*32+16 && tempy == goaly*32+16) {
		return true;
	} else {
		return false;
	}
}

sf::Vector3f bullet::getPosition()
{
	return sf::Vector3f(tempx, 0.0f, tempy);
}

sf::FloatRect bullet::getBounds()
{
	return sf::FloatRect(tempx - 16, tempy - 8, 32, 16);
}