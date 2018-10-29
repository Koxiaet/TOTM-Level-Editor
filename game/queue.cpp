#include "stage.hpp"

void manageQueue(std::queue<sf::Sound>& q) //play mode
{
	while (!q.empty()) {
		if (q.front().getStatus() == sf::Sound::Stopped) {
			q.pop();
		} else {
			break;
		}
	}
}

void addToQueue(std::queue<sf::Sound>& q, const sf::Sound s, const sf::Vector3f pos) //play mode
{
	q.push(s);
	q.back().setPosition(pos);
	if (pos != sf::Vector3f(0, 0, 0)) {
		q.back().setMinDistance(32);
		q.back().setAttenuation(0.4);
		q.back().setRelativeToListener(false);
	} else {
		q.back().setRelativeToListener(true);
	}
	q.back().play();
}