#include <SFML/Graphics.hpp>
#include "../colors.hpp"

#ifndef __KAI__TOTM__BULLET__
#define __KAI__TOTM__BULLET__ 1

class bullet
{
protected:
	size_t goalx;
	size_t goaly;
	size_t tempx;
	size_t tempy;
	float  angle;
public:
	bullet();
	bullet(const size_t _goalx, const size_t _goaly, const size_t _tempx, const size_t _tempy, const float _angle);
	bool draw(sf::RenderWindow& window, sf::Sprite& spr_bullet); //returns whether journey has finished
	sf::Vector3f getPosition();
	sf::FloatRect getBounds();
};

#endif