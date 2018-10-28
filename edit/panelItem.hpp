#include <SFML/Graphics.hpp>
#include <string>

#ifndef __KAI__TOTM__PANELITEM__
#define __KAI__TOTM__PANELITEM__ 1

class panelItem
{
public:
	sf::Sprite* sprite;
	std::string name;
	uint        id;
	panelItem(sf::Sprite* _sprite, std::string _name, uint _id): sprite(_sprite), name(_name), id(_id) {}
	panelItem(std::string _name, uint _id): sprite(NULL), name(_name), id(_id) {}
};

#endif