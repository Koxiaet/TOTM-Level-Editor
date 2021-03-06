#include "stage.hpp"
#include "files.hpp"
#include "soundGenerator.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>

#define key(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)
#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

void stage::dealloc()
{
	if (tiles == NULL) {
		return;
	}
	for (size_t i = 0; i < width; i++) {
		delete [] tiles[i];
	}
	delete [] tiles;
	tiles = NULL;
}

void stage::alloc()
{
	dealloc();
	tiles  = new tile*[width];
	for (size_t i = 0; i < width; i++) {
		tiles[i] = new tile[height];
	}
}

void stage::realloc(const int top, const int left, const int bottom, const int right) //edit mode
{
	if (tiles == NULL) {
		return;
	}
	if (top == 0 && left == 0 && bottom == 0 && right == 0) {
		return;
	}
	size_t      newwidth  = width  + left + right;
	size_t      newheight = height + top  + bottom;
	tile** newtiles  = new tile*[newwidth];
	for (size_t i = 0; i < newwidth; i++) {
		newtiles[i] = new tile[newheight];
		for (size_t j = 0; j < newheight; j++) {
			int oldi = (int)i - left;
			int oldj = (int)j - top;
			if (oldi < 0 || oldi >= (int)width || oldj < 0 || oldj >= (int)height) {
				newtiles[i][j] = air;
			} else {
				newtiles[i][j] = tiles[oldi][oldj];
			}
		}
	}
	dealloc();
	tiles  = newtiles;
	width  = newwidth;
	height = newheight;

	scrollx -= (-left)*32;
	scrolly -= (-top)*32;
}

void stage::removeEmpty() //edit mode
{
	//test whether the entire thing is empty
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			if (tiles[i][j].type != air) {
				goto notCompletelyEmpty;
			}
		}
	}
	//if control reaches here, the entire grid is empty.
	dealloc();
	width  = 0;
	height = 0;

	notCompletelyEmpty: //if there are some items
	//test if any rows or columns on the edges are empty; if so, delete them
	//this code is really ugly
	int top    = 0;
	int left   = 0;
	int bottom = 0;
	int right  = 0;

	//remove empty left columns
	while (true) { //so that multiple rows/colums can be removed in one frame
		for (size_t j = 0; j < height; j++) {
			if (tiles[left][j].type != air) { //if it encounters a block, and so the loop stops
				goto allLeftColsRemoved; // essentially a nested break
			}
		}
		left++;  //left increments to count the columns, but we later invert the sign
		if (left >= (int)width) { //if stage is completely empty, to prevent a segfault
			goto allLeftColsRemoved;
		}
	}
	allLeftColsRemoved:
	left = -left;

	//remove empty right columns
	while (true) {
		for (size_t j = 0; j < height; j++) {
			if (tiles[width - right - 1][j].type != air) {
				goto allRightColsRemoved;
			}
		}
		right++;
		if (right >= (int)width) {
			goto allRightColsRemoved;
		}
	}
	allRightColsRemoved:
	right = -right;

	//remove empty top rows
	while (true) {
		for (size_t i = 0; i < width; i++) {
			if (tiles[i][top].type != air) {
				goto allTopRowsRemoved;
			}
		}
		top++;
		if (top >= (int)height) {
			goto allTopRowsRemoved;
		}
	}
	allTopRowsRemoved:
	top = -top;

	//remove empty bottom rows
	while (true) {
		for (size_t i = 0; i < width; i++) {
			if (tiles[i][height - bottom - 1].type != air) {
				goto allBottomRowsRemoved;
			}
		}
		bottom++;
		if (bottom >= (int)height) {
			goto allBottomRowsRemoved;
		}
	}
	allBottomRowsRemoved:
	bottom = -bottom;

	//std::cout << "top: " << top << " left: " << left << " bottom: " << bottom << " right: " << right << std::endl;
	realloc(top, left, bottom, right);
}

tile& stage::standingOn() //play mode
{
	switch (player.facing) {
		case up:    return tiles[player.x][player.y-1];
		case down:  return tiles[player.x][player.y+1];
		case left:  return tiles[player.x-1][player.y];
		case right: return tiles[player.x+1][player.y];
	}
	return tiles[player.x][player.y]; //ERROR
}

void stage::killPlayer() //play mode
{
	player.kill();
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			if (tiles[i][j].type == ccoin) {
				tiles[i][j].type = coin;
			} else if (tiles[i][j].type == brokenBlock) {
				tiles[i][j].type = breakableBlock;
			}
		}
	}
	win = false;
}

stage::stage():
	mode(undefined),
	width(0),
	height(0),
	scrollx(-400),
	scrolly(-300),
	tiles(NULL),
	openFileName("Untitled"),
	win(false),
	barTimer(0),
	colorTimer(0),
	unsavedChanges(false)
	
{
	tex_coin.loadFromFile("game/images/coin.png");
	tex_coin.setSmooth(false);
	spr_coin.setTexture(tex_coin);
	spr_coin.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_coin.setOrigin(8, 8);
	spr_coin.setColor(COL_MED);

	tex_brick.loadFromFile("game/images/brick.png");
	tex_brick.setSmooth(false);
	spr_brick.setTexture(tex_brick);
	spr_brick.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_brick.setOrigin(8, 8);
	spr_brick.setColor(COL_LOW);

	tex_spikes.loadFromFile("game/images/spikes.png");
	tex_spikes.setSmooth(false);
	spr_spikes.setTexture(tex_spikes);
	spr_spikes.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_spikes.setOrigin(8, 8);
	spr_spikes.setColor(COL_HIGH);

	tex_spikeHider.loadFromFile("game/images/spikeHider.png");
	tex_spikeHider.setSmooth(false);
	spr_spikeHider.setTexture(tex_spikeHider);
	spr_spikeHider.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_spikeHider.setOrigin(8, 8);
	spr_spikeHider.setColor(COL_LOW);

	tex_smallHiddenSpikes.loadFromFile("game/images/smallHiddenSpikes.png");
	tex_smallHiddenSpikes.setSmooth(false);
	spr_smallHiddenSpikes.setTexture(tex_smallHiddenSpikes);
	spr_smallHiddenSpikes.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_smallHiddenSpikes.setOrigin(8, 8);
	spr_smallHiddenSpikes.setColor(COL_HIGH);

	tex_hiddenSpikes.loadFromFile("game/images/hiddenSpikes.png");
	tex_hiddenSpikes.setSmooth(false);
	spr_hiddenSpikes.setTexture(tex_hiddenSpikes);
	spr_hiddenSpikes.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_hiddenSpikes.setOrigin(8, 8);
	spr_hiddenSpikes.setColor(COL_HIGH);

	tex_player.loadFromFile("game/images/player.png");
	tex_player.setSmooth(false);
	spr_player.setTexture(tex_player);
	spr_player.setTextureRect(sf::IntRect(0, 0, 16, 16));
	spr_player.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_player.setOrigin(8, 8);
	spr_player.setColor(COL_MED);

	tex_player_moving.loadFromFile("game/images/playerMoving.png");
	tex_player_moving.setSmooth(false);
	spr_player_moving.setTexture(tex_player_moving);
	spr_player_moving.setTextureRect(sf::IntRect(0, 0, 16, 16));
	spr_player_moving.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_player_moving.setOrigin(8, 8);
	spr_player_moving.setColor(COL_MED);

	tex_shooter.loadFromFile("game/images/shooter.png");
	tex_shooter.setSmooth(false);
	spr_shooter_up.setTexture(tex_shooter);
	spr_shooter_up.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_shooter_up.setOrigin(8, 8);
	spr_shooter_up.setRotation(90);
	spr_shooter_up.setColor(COL_LOW);
	spr_shooter_down.setTexture(tex_shooter);
	spr_shooter_down.setScale(sf::Vector2f(-2.0f, 2.0f));
	spr_shooter_down.setOrigin(8, 8);
	spr_shooter_down.setRotation(90);
	spr_shooter_down.setColor(COL_LOW);
	spr_shooter_left.setTexture(tex_shooter);
	spr_shooter_left.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_shooter_left.setOrigin(8, 8);
	spr_shooter_left.setRotation(0);
	spr_shooter_left.setColor(COL_LOW);
	spr_shooter_right.setTexture(tex_shooter);
	spr_shooter_right.setScale(sf::Vector2f(-2.0f, 2.0f));
	spr_shooter_right.setOrigin(8, 8);
	spr_shooter_right.setColor(COL_LOW);

	tex_shooter_open.loadFromFile("game/images/shooterOpen.png");
	tex_shooter_open.setSmooth(false);
	spr_shooter_open_up.setTexture(tex_shooter_open);
	spr_shooter_open_up.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_shooter_open_up.setOrigin(8, 8);
	spr_shooter_open_up.setRotation(90);
	spr_shooter_open_up.setColor(COL_HIGH);
	spr_shooter_open_down.setTexture(tex_shooter_open);
	spr_shooter_open_down.setScale(sf::Vector2f(-2.0f, 2.0f));
	spr_shooter_open_down.setOrigin(8, 8);
	spr_shooter_open_down.setRotation(90);
	spr_shooter_open_down.setColor(COL_HIGH);
	spr_shooter_open_left.setTexture(tex_shooter_open);
	spr_shooter_open_left.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_shooter_open_left.setOrigin(8, 8);
	spr_shooter_open_left.setRotation(0);
	spr_shooter_open_left.setColor(COL_HIGH);
	spr_shooter_open_right.setTexture(tex_shooter_open);
	spr_shooter_open_right.setScale(sf::Vector2f(-2.0f, 2.0f));
	spr_shooter_open_right.setOrigin(8, 8);
	spr_shooter_open_right.setColor(COL_HIGH);

	tex_breakableBlock.loadFromFile("game/images/breakableBlock.png");
	tex_breakableBlock.setSmooth(false);
	spr_breakableBlock.setTexture(tex_breakableBlock);
	spr_breakableBlock.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_breakableBlock.setOrigin(8, 8);
	spr_breakableBlock.setColor(COL_LOW);

	tex_goal.loadFromFile("game/images/goal.png");
	tex_goal.setSmooth(false);
	spr_goal.setTexture(tex_goal);
	spr_goal.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_goal.setOrigin(8, 8);
	spr_goal.setColor(COL_MED);

	tex_bullet.loadFromFile("game/images/bullet.png");
	tex_bullet.setSmooth(false);
	spr_bullet.setTexture(tex_bullet);
	spr_bullet.setScale(sf::Vector2f(2.0f, 2.0f));
	spr_bullet.setOrigin(8, 8);
	spr_bullet.setColor(COL_HIGH);

	tex_pause.loadFromFile("game/images/pauseIcon.png");
	tex_pause.setSmooth(false);
	spr_pause.setTexture(tex_pause);
	spr_pause.setOrigin(8, 0);
	spr_pause.setScale(sf::Vector2f(4.0f, 4.0f));
	spr_pause.setColor(COL_MED);

	buf_move = squareWave(105, 6, 2000);
	snd_move.setBuffer(buf_move);

	buf_coin = dimSquareWave(525, 20, 1000, 20);
	snd_coin.setBuffer(buf_coin);

	buf_bullet_launch = fallingSquareWave(1000, 300, 20, 2000);
	snd_bullet_launch.setBuffer(buf_bullet_launch);

	buf_blade.loadFromFile("game/sounds/blade.ogg");
	snd_blade.setBuffer(buf_blade);

	buf_breakableBlock = squareWave(210, 2, 2000);
	snd_breakableBlock.setBuffer(buf_breakableBlock);

	fnt_totm.loadFromFile("totm.ttf");
	txt_coins.setFont(fnt_totm);
	txt_coins.setCharacterSize(20);
	txt_coins.setFillColor(COL_MED);

	txt_you_win.setFont(fnt_totm);
	txt_you_win.setCharacterSize(20);
	txt_you_win.setFillColor(COL_NONE);

	menubar.items.push_back(menuSection("FILE"));
	menubar.items[0].items.push_back(menuItem("NEW"));
	menubar.items[0].items[0].shortcut.push_back(sf::Keyboard::LSystem);
	menubar.items[0].items[0].shortcut.push_back(sf::Keyboard::N);
	menubar.items[0].items.push_back(menuItem("OPEN..."));
	menubar.items[0].items[1].shortcut.push_back(sf::Keyboard::LSystem);
	menubar.items[0].items[1].shortcut.push_back(sf::Keyboard::O);
	menubar.items[0].items.push_back(menuItem("SAVE"));
	menubar.items[0].items[2].shortcut.push_back(sf::Keyboard::LSystem);
	menubar.items[0].items[2].shortcut.push_back(sf::Keyboard::S);
	menubar.items[0].items.push_back(menuItem("SAVE AS..."));
	menubar.items[0].items[3].shortcut.push_back(sf::Keyboard::LSystem);
	menubar.items[0].items[3].shortcut.push_back(sf::Keyboard::LShift);
	menubar.items[0].items[3].shortcut.push_back(sf::Keyboard::S);

	oldMousePos.x = 0;
	oldMousePos.y = 0;

	cur_default.loadFromSystem(sf::Cursor::Arrow);
	cur_hand.loadFromSystem(sf::Cursor::Hand);

	panel.items.push_back(panelItem("AIR", air));
	panel.items.push_back(panelItem(&spr_coin, "COIN", coin));
	panel.items.push_back(panelItem(&spr_brick, "BRICK", brick));
	panel.items.push_back(panelItem(&spr_spikes, "SPIKES", spikes));
	panel.items.push_back(panelItem(&spr_spikeHider, "HIDDEN SPIKES", spikeHider));
	panel.items.push_back(panelItem(&spr_player, "PLAYER", tile_player));
	panel.items.push_back(panelItem(&spr_breakableBlock, "BREAKABLE BLOCK", breakableBlock));
	panel.items.push_back(panelItem(&spr_goal, "GOAL", goal));
	panel.items.push_back(panelItem(&spr_shooter_up, "SHOOTER UP", shooter_up));
	panel.items.push_back(panelItem(&spr_shooter_down, "SHOOTER DOWN", shooter_down));
	panel.items.push_back(panelItem(&spr_shooter_left, "SHOOTER LEFT", shooter_left));
	panel.items.push_back(panelItem(&spr_shooter_right, "SHOOTER RIGHT", shooter_right));

	bars.setFillColor(COL_NONE);
}

size_t stage::getWidth()
{
	return width;
}

size_t stage::getHeight()
{
	return height;
}

bool stage::pausePressed(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (spr_pause.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			return true;
		}
	}
	if (key(Escape)) {
		return true;
	}
	return false;
}

void stage::scroll(sf::RenderWindow& window) //edit mode
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (mouse(Middle)) {
		scrollx += oldMousePos.x - mousePos.x;
		scrolly += oldMousePos.y - mousePos.y;
		window.setMouseCursor(cur_hand);
	}

	oldMousePos = mousePos;
}

void stage::controlPlayer() //play mode
{
	if (mode != playing) {
		return;
	}
	if (win) {
		return;
	}
	if (player.x*32+16 == player.tempx && player.y*32+16 == player.tempy) { //if player is not moving
		player.oldx = player.x;
		player.oldy = player.y;
		if (key(Up)) {
			size_t dy = 0;
			collisionType collision = tiles[player.x][player.y-dy].getCollisionType();
			while (collision == pass || collision == breakable) {
				dy++;
				collision = tiles[player.x][player.y-dy].getCollisionType();
			}
			player.y -= --dy;
			if (dy > 0) {
				snd_move.setPosition(0,0,0);
				snd_move.setRelativeToListener(true);
				snd_move.play();
			}
			player.facing = up;
		} else if (key(Down)) {
			size_t dy = 0;
			collisionType collision = tiles[player.x][player.y+dy].getCollisionType();
			while (collision == pass || collision == breakable) {
				dy++;
				collision = tiles[player.x][player.y+dy].getCollisionType();
			}
			player.y += --dy;
			if (dy > 0) {
				snd_move.setPosition(0,0,0);
				snd_move.setRelativeToListener(true);
				snd_move.play();
			}
			player.facing = down;
		} else if (key(Right)) {
			size_t dx = 0;
			collisionType collision = tiles[player.x+dx][player.y].getCollisionType();
			while (collision == pass || collision == breakable) {
				dx++;
				collision = tiles[player.x+dx][player.y].getCollisionType();
			}
			player.x += --dx;
			if (dx > 0) {
				snd_move.setPosition(0,0,0);
				snd_move.setRelativeToListener(true);
				snd_move.play();
			}
			player.facing = right;
		} else if (key(Left)) {
			size_t dx = 0;
			collisionType collision = tiles[player.x-dx][player.y].getCollisionType();
			while (collision == pass || collision == breakable) {
				dx++;
				collision = tiles[player.x-dx][player.y].getCollisionType();
			}
			player.x -= --dx;
			if (dx > 0) {
				snd_move.setPosition(0,0,0);
				snd_move.setRelativeToListener(true);
				snd_move.play();
			}
			player.facing = left;
		}
	} else {
		const size_t speed = 32;
		if (player.tempx < player.x*32+16) {
			player.tempx += speed;
			if (player.tempx > player.x*32+16) {
				player.tempx = player.x*32+16;
			}
		} else if (player.tempx > player.x*32+16) {
			player.tempx -= speed;
			if (player.tempx < player.x*32+16) {
				player.tempx = player.x*32+16;
			}
		} else if (player.tempy < player.y*32+16) {
			player.tempy += speed;
			if (player.tempy > player.y*32+16) {
				player.tempy = player.y*32+16;
			}
		} else if (player.tempy > player.y*32+16) {
			player.tempy -= speed;
			if (player.tempy < player.y*32+16) {
				player.tempy = player.y*32+16;
			}
		}
		const size_t tempxt = (player.tempx-16)/32;
		const size_t tempyt = (player.tempy-16)/32;
		if (tiles[tempxt-1][tempyt].type == spikeHider && tiles[tempxt-1][tempyt].spikeTimerR == 0) {
			tiles[tempxt-1][tempyt].spikeTimerR = 1;
		}
		if (tiles[tempxt+1][tempyt].type == spikeHider && tiles[tempxt+1][tempyt].spikeTimerL == 0) {
			tiles[tempxt+1][tempyt].spikeTimerL = 1;
		}
		if (tiles[tempxt][tempyt-1].type == spikeHider && tiles[tempxt][tempyt-1].spikeTimerD == 0) {
			tiles[tempxt][tempyt-1].spikeTimerD = 1;
		}
		if (tiles[tempxt][tempyt+1].type == spikeHider && tiles[tempxt][tempyt+1].spikeTimerU == 0) {
			tiles[tempxt][tempyt+1].spikeTimerU = 1;
		}
	}
	if (player.x*32+16 == player.tempx && player.y*32+16 == player.tempy) { //has finished journey
		if (standingOn().type == spikes) { //if dies
			killPlayer();
		}
		if (standingOn().type == goal) { //if wins
			win = true;
		}
	}
	const size_t tempxtmin = (player.tempx-16)/32;
	const size_t tempytmin = (player.tempy-16)/32;
	const size_t tempxtmax = (player.tempx+15)/32;
	const size_t tempytmax = (player.tempy+15)/32;
	const uint spikeTimerMin = 40;

	if (tiles[tempxtmax][tempytmax].type == coin) {
		tiles[tempxtmax][tempytmax].type = ccoin;
		player.coins++;
		addToQueue(que_coin, snd_coin);
	}
	if (tiles[tempxtmin][tempytmin].type == coin) {
		tiles[tempxtmin][tempytmin].type = ccoin;
		player.coins++;
		addToQueue(que_coin, snd_coin);
	}

	if (tiles[tempxtmin][tempytmin-1].spikeTimerD > spikeTimerMin && tiles[tempxtmin][tempytmin-1].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmin][tempytmin+1].spikeTimerU > spikeTimerMin && tiles[tempxtmin][tempytmin+1].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmin-1][tempytmin].spikeTimerR > spikeTimerMin && tiles[tempxtmin-1][tempytmin].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmin+1][tempytmin].spikeTimerL > spikeTimerMin && tiles[tempxtmin+1][tempytmin].type == spikeHider) {
		killPlayer();
	}
	
	if (tiles[tempxtmax][tempytmax-1].spikeTimerD > spikeTimerMin && tiles[tempxtmin][tempytmin-1].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmax][tempytmax+1].spikeTimerU > spikeTimerMin && tiles[tempxtmin][tempytmin+1].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmax-1][tempytmax].spikeTimerR > spikeTimerMin && tiles[tempxtmin-1][tempytmin].type == spikeHider) {
		killPlayer();
	}
	if (tiles[tempxtmax+1][tempytmax].spikeTimerL > spikeTimerMin && tiles[tempxtmin+1][tempytmin].type == spikeHider) {
		killPlayer();
	}

	if (tiles[tempxtmin][tempytmin].type == breakableBlock) {
		tiles[tempxtmin][tempytmin].type = brokenBlock;
		addToQueue(que_breakableBlock, snd_breakableBlock);
	}
	if (tiles[tempxtmax][tempytmax].type == breakableBlock) {
		tiles[tempxtmax][tempytmax].type = brokenBlock;
		addToQueue(que_breakableBlock, snd_breakableBlock);
	}

	if (key(R)) {
		killPlayer();
	}
}

void stage::changeToEditMode()
{
	if (mode != editing) {
		killPlayer();
		mode = editing;
		spr_player.setRotation(0);
	}
}

int  stage::changeToPlayMode()
{
	if (mode != playing) {
		if (tiles == NULL) {
			if (open() == 1) { //failed to open
				return 1;
			}
		}
		mode = playing;
		uint changedPlayerPos = 0;
		for (size_t i = 0; i < width; i++) {
			for (size_t j = 0; j < height; j++) {
				if (tiles[i][j].type == tile_player) {
					player.teleport(i, j, down, true);
					changedPlayerPos++;
				}
			}
		}

		if (changedPlayerPos == 0) { //no player
			std::cout << "Error: No Player." << std::endl;
			return 1;
		}
		if (changedPlayerPos > 1) {
			std::cout << "Warning: More than one player." << std::endl;
		}

		return 0;
	}
	return 0;
}

stage::~stage()
{
	dealloc();
}