#include "../edit/menu/menubar.hpp"
#include "../edit/panel.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <queue>

#ifndef __KAI__TOTM__STAGE__
#define __KAI__TOTM__STAGE__ 1

#define key(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)

class stage
{
protected:
	bool editMode; //playing or editing?
	size_t width;
	size_t height;
	sf::Vector2i oldMousePos; //for edit mode: moving camera around with middle click
	int scrollx; //edit mode
	int scrolly; //edit mode
	tile** tiles;

	sf::Texture tex_coin;
	sf::Sprite  spr_coin;

	sf::Texture tex_brick;
	sf::Sprite  spr_brick;

	sf::Texture tex_spikes;
	sf::Sprite  spr_spikes;

	sf::Texture tex_spikeHider;
	sf::Sprite  spr_spikeHider;

	sf::Texture tex_smallHiddenSpikes; //play mode
	sf::Sprite  spr_smallHiddenSpikes; //play mode

	sf::Texture tex_hiddenSpikes; //play mode
	sf::Sprite  spr_hiddenSpikes; //play mode

	sf::Texture tex_player;
	sf::Sprite  spr_player;

	sf::Texture tex_shooter;
	sf::Sprite  spr_shooter_up;
	sf::Sprite  spr_shooter_down;
	sf::Sprite  spr_shooter_left;
	sf::Sprite  spr_shooter_right;

	sf::Texture tex_shooter_open;
	sf::Sprite  spr_shooter_open_up;
	sf::Sprite  spr_shooter_open_down;
	sf::Sprite  spr_shooter_open_left;
	sf::Sprite  spr_shooter_open_right;

	sf::Texture tex_breakableBlock;
	sf::Sprite  spr_breakableBlock;

	sf::Texture tex_bullet;
	sf::Sprite  spr_bullet;
	std::vector<bullet> vec_bullet;

	sf::Texture tex_pause;
	sf::Sprite  spr_pause;

	sf::SoundBuffer       buf_move; //play mode
	sf::Sound             snd_move; //play mode

	sf::SoundBuffer       buf_coin; //play mode
	sf::Sound             snd_coin; //play mode
	std::queue<sf::Sound> que_coin; //play mode

	sf::SoundBuffer       buf_blade; //play mode
	sf::Sound             snd_blade; //play mode
	std::queue<sf::Sound> que_blade; //play mode

	sf::SoundBuffer       buf_bullet_launch; //play mode
	sf::Sound             snd_bullet_launch; //play mode
	std::queue<sf::Sound> que_bullet_launch; //play mode

	sf::SoundBuffer       buf_breakableBlock; //play mode
	sf::Sound             snd_breakableBlock; //play mode
	std::queue<sf::Sound> que_breakableBlock; //play mode

	sf::Font fnt_totm;
	sf::Text txt_coins; //play mode

	sf::Cursor cur_default; //edit mode
	sf::Cursor cur_hand; //edit mode

	menubar menubar; //edit mode
	panel panel; //edit mode

	std::string openFileName; //edit mode

	void dealloc();
	void alloc();
	void realloc(const int top, const int left, const int bottom, const int right); //edit mode
	void removeEmpty(); //edit mode
	//each one is the difference: 0, -1, 1, 0 extends the rectangle one down, and removes the leftmost column

	tile& standingOn(); //play mode
	void killPlayer(); //play mode

	void newStage(); //edit mode
	int  open(); //returns 1 on failure
	void save(); //edit mode
	void saveAs(); //edit mode

	void drawTile(sf::RenderWindow& window, sf::Sprite& tile, const size_t i, const size_t j);
	void drawPreviewTile(sf::RenderWindow& window, sf::Sprite& tile, const int previewx, const int previewy); //edit mode

	void updateBullets(sf::RenderWindow& window);
public:
	player player;
	bool unsavedChanges;
	stage();
	size_t getWidth();
	size_t getHeight();
	int loadFromHex(const std::string filename);
	int saveToHex(const std::string filename); //edit mode

	bool pausePressed(sf::RenderWindow& window);
	void scroll(sf::RenderWindow& window); //edit mode
	void controlPlayer(); //play mode

	void changeToEditMode(); // this functions change from edit to play mode and vice versa
	int  changeToPlayMode(); //returns 1 if fails

	int warnUnsavedChanges();

	void draw(sf::RenderWindow& window, bool disableClick = false);
	~stage();
};

void manageQueue(std::queue<sf::Sound>& q, const sf::Vector3f lpos = sf::Vector3f(0, 0, 0)); //play mode
void addToQueue(std::queue<sf::Sound>& q, const sf::Sound s, const sf::Vector3f pos = sf::Vector3f(0, 0, 0)); //play mode

#endif