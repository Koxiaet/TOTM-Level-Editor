#include <cstdint>

#ifndef __KAI__TOTM__TILE__
#define __KAI__TOTM__TILE__ 1

enum tiletypeEnum: uint8_t
{
	air = 0,
	coin = 1,
	ccoin = 2,
	brick = 3,
	spikes = 4,
	spikeHider = 5,
	tile_player = 6,
	shooter_up = 7,
	shooter_down = 8,
	shooter_left = 9,
	shooter_right = 10,
	breakableBlock = 11,
	brokenBlock = 12
};

typedef uint8_t tiletype;

enum collisionTypeEnum: uint8_t
{
	pass,
	solid,
	breakable
};

typedef uint8_t collisionType;

class tile
{
public:
	tiletype type;
	unsigned int spikeTimerU; //also used for the timer of shooters
	unsigned int spikeTimerD;
	unsigned int spikeTimerL;
	unsigned int spikeTimerR;
	tile(): type(air), spikeTimerU(0), spikeTimerD(0), spikeTimerL(0), spikeTimerR(0) {};
	tile(const tiletype& t): type(t), spikeTimerU(0), spikeTimerD(0), spikeTimerL(0), spikeTimerR(0) {};
	tile(const tile& t): type(t.type), spikeTimerU(0), spikeTimerD(0), spikeTimerL(0), spikeTimerR(0) {};
	tile& operator=(const tile& t)
	{
		type = t.type;
		return *this;
	}
	tile& operator=(const uint8_t& t)
	{
		type = t;
		return *this;
	}
	collisionType getCollisionType()
	{
		switch (type) {
			case air: return pass;
			case coin: return pass;
			case ccoin: return pass;
			case brick: return solid;
			case spikes: return solid;
			case spikeHider: return solid;
			case tile_player: return pass;
			case shooter_up: return solid;
			case shooter_down: return solid;
			case shooter_left: return solid;
			case shooter_right: return solid;
			case breakableBlock: return breakable;
			case brokenBlock: return pass;
			default: return pass; //also error but nvm
		}
	}
};


#endif