#include "stage.hpp"
#include "files.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>

void stage::drawTile(sf::RenderWindow& window, sf::Sprite& tile, const size_t i, const size_t j)
{
	tile.setPosition(i*32 + 16, j*32 + 16);
	window.draw(tile);
}

void stage::drawPreviewTile(sf::RenderWindow& window, sf::Sprite& tile, const int previewx, const int previewy) //edit mode
{
	const sf::Color normal       = sf::Color(0xFF, 0xFF, 0xFF, 0xFF);
	const sf::Color transparency = sf::Color(0xFF, 0xFF, 0xFF, 0xA0);

	tile.setPosition(previewx, previewy);
	tile.setColor(transparency);
	window.draw(tile);
	tile.setColor(normal);
}

void stage::updateBullets(sf::RenderWindow& window)
{
	for (size_t i = 0; i < vec_bullet.size(); i++) {
		if (vec_bullet[i].getBounds().intersects(player.getBounds())) {
			killPlayer();
		}
		if (vec_bullet[i].draw(window, spr_bullet)) { //finished
			vec_bullet.erase(vec_bullet.begin()+i);
			i--;
		}
	}
}

void stage::draw(sf::RenderWindow& window, bool disableClick)
{
	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	//this manages the title, scrolling and view moving for edit and play mode respectively
	//if in play mode and no stage is open, open one
	if (editMode) {
		if (unsavedChanges) {
			window.setTitle("*" + getName(openFileName) + " - TOTM Editor*");
		} else {
			window.setTitle(getName(openFileName) + " - TOTM Editor");
		}
		
		scroll(window);
		view.setCenter(scrollx + (int)window.getSize().x/2, scrolly + (int)window.getSize().y/2);
	} else {
		window.setTitle("Tomb of the Mask");
		view.setCenter(player.tempx, player.tempy);
	}

	window.setMouseCursor(cur_default);
	window.setView(view);

	//this manages drawing the tiles in both modes

	const uint shootTimerMax = 60;
	const uint shootAnimMax = 5;

	if (tiles != NULL) {
		for (size_t i = 0; i < width; i++) {
			for (size_t j = 0; j < height; j++) {
				switch (tiles[i][j].type) {
					case coin:
						drawTile(window, spr_coin, i, j);
						break;
					case brick:
						drawTile(window, spr_brick, i, j);
						break;
					case spikes:
						drawTile(window, spr_spikes, i, j);
						break;
					case spikeHider: {
						const uint spikeTimerMin = 40;
						const uint spikeTimerMax = 80;
						if (tiles[i][j].spikeTimerU > 0) {
							tiles[i][j].spikeTimerU++;
							if (tiles[i][j].spikeTimerU > spikeTimerMin) {
								spr_hiddenSpikes.setPosition(i*32+16, j*32+16-32);
								spr_hiddenSpikes.setRotation(0);
								window.draw(spr_hiddenSpikes);
								if (tiles[i][j].spikeTimerU == spikeTimerMin+1) {
									addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
								}
							} else {
								spr_smallHiddenSpikes.setPosition(i*32+16, j*32+16-32);
								spr_smallHiddenSpikes.setRotation(0);
								window.draw(spr_smallHiddenSpikes);
							}
							if (tiles[i][j].spikeTimerU > spikeTimerMax) {
								tiles[i][j].spikeTimerU = 0;
								addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
							}
						}
						if (tiles[i][j].spikeTimerD > 0) {
							tiles[i][j].spikeTimerD++;
							if (tiles[i][j].spikeTimerD > spikeTimerMin) {
								spr_hiddenSpikes.setPosition(i*32+16, j*32+16+32);
								spr_hiddenSpikes.setRotation(180);
								window.draw(spr_hiddenSpikes);
								if (tiles[i][j].spikeTimerD == spikeTimerMin+1) {
									addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
								}
							} else {
								spr_smallHiddenSpikes.setPosition(i*32+16, j*32+16+32);
								spr_smallHiddenSpikes.setRotation(180);
								window.draw(spr_smallHiddenSpikes);
							}
							if (tiles[i][j].spikeTimerD > spikeTimerMax) {
								tiles[i][j].spikeTimerD = 0;
								addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
							}
						}
						if (tiles[i][j].spikeTimerL > 0) {
							tiles[i][j].spikeTimerL++;
							if (tiles[i][j].spikeTimerL > spikeTimerMin) {
								spr_hiddenSpikes.setPosition(i*32+16-32, j*32+16);
								spr_hiddenSpikes.setRotation(270);
								window.draw(spr_hiddenSpikes);
								if (tiles[i][j].spikeTimerL == spikeTimerMin+1) {
									addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
								}
							} else {
								spr_smallHiddenSpikes.setPosition(i*32+16-32, j*32+16);
								spr_smallHiddenSpikes.setRotation(270);
								window.draw(spr_smallHiddenSpikes);
							}
							if (tiles[i][j].spikeTimerL > spikeTimerMax) {
								tiles[i][j].spikeTimerL = 0;
								addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
							}
						}
						if (tiles[i][j].spikeTimerR > 0) {
							tiles[i][j].spikeTimerR++;
							if (tiles[i][j].spikeTimerR > spikeTimerMin) {
								spr_hiddenSpikes.setPosition(i*32+16+32, j*32+16);
								spr_hiddenSpikes.setRotation(90);
								window.draw(spr_hiddenSpikes);
								if (tiles[i][j].spikeTimerR == spikeTimerMin+1) {
									addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
								}
							} else {
								spr_smallHiddenSpikes.setPosition(i*32+16+32, j*32+16);
								spr_smallHiddenSpikes.setRotation(90);
								window.draw(spr_smallHiddenSpikes);
							}
							if (tiles[i][j].spikeTimerR > spikeTimerMax) {
								tiles[i][j].spikeTimerR = 0;
								addToQueue(que_blade, snd_blade, sf::Vector3f(i*32+16, 0.0f, j*32+16));
							}
						}
						drawTile(window, spr_spikeHider, i, j);
						break;
					}
					case tile_player:
						if (editMode) {
							drawTile(window, spr_player, i, j);
						}
						break;
					case shooter_up:
						if (editMode) {
							drawTile(window, spr_shooter_up, i, j);
						} else {
							tiles[i][j].spikeTimerU++;
							if (tiles[i][j].spikeTimerU >= shootTimerMax-shootAnimMax) {
								drawTile(window, spr_shooter_open_up, i, j);
							} else {
								drawTile(window, spr_shooter_up, i, j);
							}
							if (tiles[i][j].spikeTimerU == shootTimerMax-shootAnimMax) {
								//shoot bullet
								size_t tempx = i;
								size_t tempy = j-1;
								size_t goalx = tempx;
								size_t goaly = tempy;
								while (tiles[goalx][goaly].getCollisionType() == pass) {
									goaly--;
								}
								goaly++;
								vec_bullet.push_back(bullet(goalx, goaly, tempx, tempy, 270));
								addToQueue(que_bullet_launch, snd_bullet_launch, sf::Vector3f(i*32 + 16, 0.0f, j*32 + 16));
							}
							if (tiles[i][j].spikeTimerU > shootTimerMax) {
								tiles[i][j].spikeTimerU = 0;
							}
						}
						break;
					case shooter_down:
						if (editMode) {
							drawTile(window, spr_shooter_down, i, j);
						} else {
							tiles[i][j].spikeTimerU++;
							if (tiles[i][j].spikeTimerU >= shootTimerMax-shootAnimMax) {
								drawTile(window, spr_shooter_open_down, i, j);
							} else {
								drawTile(window, spr_shooter_down, i, j);
							}
							if (tiles[i][j].spikeTimerU == shootTimerMax-shootAnimMax) {
								//shoot bullet
								size_t tempx = i;
								size_t tempy = j+1;
								size_t goalx = tempx;
								size_t goaly = tempy;
								while (tiles[goalx][goaly].getCollisionType() == pass) {
									goaly++;
								}
								goaly--;
								vec_bullet.push_back(bullet(goalx, goaly, tempx, tempy, 90));
								addToQueue(que_bullet_launch, snd_bullet_launch, sf::Vector3f(i*32 + 16, 0.0f, j*32 + 16));
							}
							if (tiles[i][j].spikeTimerU > shootTimerMax) {
								tiles[i][j].spikeTimerU = 0;
							}
						}
						break;
					case shooter_left:
						if (editMode) {
							drawTile(window, spr_shooter_left, i, j);
						} else {
							tiles[i][j].spikeTimerU++;
							if (tiles[i][j].spikeTimerU >= shootTimerMax-shootAnimMax) {
								drawTile(window, spr_shooter_open_left, i, j);
							} else {
								drawTile(window, spr_shooter_left, i, j);
							}
							if (tiles[i][j].spikeTimerU == shootTimerMax-shootAnimMax) {
								//shoot bullet
								size_t tempx = i-1;
								size_t tempy = j;
								size_t goalx = tempx;
								size_t goaly = tempy;
								while (tiles[goalx][goaly].getCollisionType() == pass) {
									goalx--;
								}
								goalx++;
								vec_bullet.push_back(bullet(goalx, goaly, tempx, tempy, 180));
								addToQueue(que_bullet_launch, snd_bullet_launch, sf::Vector3f(i*32 + 16, 0.0f, j*32 + 16));
							}
							if (tiles[i][j].spikeTimerU > shootTimerMax) {
								tiles[i][j].spikeTimerU = 0;
							}
						}
						break;
					case shooter_right:
						if (editMode) {
							drawTile(window, spr_shooter_right, i, j);
						} else {
							tiles[i][j].spikeTimerU++;
							if (tiles[i][j].spikeTimerU >= shootTimerMax-shootAnimMax) {
								drawTile(window, spr_shooter_open_right, i, j);
							} else {
								drawTile(window, spr_shooter_right, i, j);
							}
							if (tiles[i][j].spikeTimerU == shootTimerMax-shootAnimMax) {
								//shoot bullet
								size_t tempx = i+1;
								size_t tempy = j;
								size_t goalx = tempx;
								size_t goaly = tempy;
								while (tiles[goalx][goaly].getCollisionType() == pass) {
									goalx++;
								}
								goalx--;
								vec_bullet.push_back(bullet(goalx, goaly, tempx, tempy, 0));
								addToQueue(que_bullet_launch, snd_bullet_launch, sf::Vector3f(i*32 + 16, 0.0f, j*32 + 16));
							}
							if (tiles[i][j].spikeTimerU > shootTimerMax) {
								tiles[i][j].spikeTimerU = 0;
							}
						}
						break;
					case breakableBlock:
						drawTile(window, spr_breakableBlock, i, j);
						break;
					case goal:
						drawTile(window, spr_goal, i, j);
						break;
				}
			}
		}
		updateBullets(window);
	}

	//this manages drawing the preview and placing tiles on edit mode, and the player and sound effects on play mode

	if (editMode) {
		sf::Vector2i mpos = sf::Mouse::getPosition(window);
		if (mpos.y > 28 && mpos.x > 208) { //not on menubar or panel
			//this is the code for the translucent 'preview' of the block you are going to place
			//also for placing blocks, but that is later
			mpos.x += scrollx;
			mpos.y += scrolly;

			if (mpos.x < 0) { //i honestly have no idea why this code has to be here, but it does.
				mpos.x -= 32;
			}
			if (mpos.y < 0) {
				mpos.y -= 32;
			}

			int tilex = mpos.x/32;
			int tiley = mpos.y/32;

			const int previewx = tilex*32 + 16;
			const int previewy = tiley*32 + 16;

			switch (panel.selectedTileL) {
				case coin:
					drawPreviewTile(window, spr_coin, previewx, previewy);
					break;
				case brick:
					drawPreviewTile(window, spr_brick, previewx, previewy);
					break;
				case spikes:
					drawPreviewTile(window, spr_spikes, previewx, previewy);
					break;
				case spikeHider:
					drawPreviewTile(window, spr_spikeHider, previewx, previewy);
					break;
				case tile_player:
					drawPreviewTile(window, spr_player, previewx, previewy);
					break;
				case shooter_up:
					drawPreviewTile(window, spr_shooter_up, previewx, previewy);
					break;
				case shooter_down:
					drawPreviewTile(window, spr_shooter_down, previewx, previewy);
					break;
				case shooter_left:
					drawPreviewTile(window, spr_shooter_left, previewx, previewy);
					break;
				case shooter_right:
					drawPreviewTile(window, spr_shooter_right, previewx, previewy);
					break;
				case breakableBlock:
					drawPreviewTile(window, spr_breakableBlock, previewx, previewy);
					break;
				case goal:
					drawPreviewTile(window, spr_goal, previewx, previewy);
					break;
			}

			if ((mouse(Left) || mouse(Right)) && !disableClick) {
				//for placing blocks
				if (tiles == NULL) {
					tiles  = new tile*[0];
					width  = 0;
					height = 0;
				}

				int top    = 0;
				int left   = 0;
				int bottom = 0;
				int right  = 0;

				if (tilex < 0) {
					left = abs(tilex);
					tilex = 0;
				}
				if (tilex >= (int)width) {
					right = tilex - width + 1;
				}
				if (tiley < 0) {
					top = abs(tiley);
					tiley = 0;
				}
				if (tiley >= (int)height) {
					bottom = tiley - height + 1;
				}

				realloc(top, left, bottom, right);

				bool testEmptyRows = false;

				if (mouse(Left)) {
					tiles[tilex][tiley].type = panel.selectedTileL;
					if (panel.selectedTileL == air) {
						testEmptyRows = true;
					}
				} else if (mouse(Right)) {
					tiles[tilex][tiley].type = panel.selectedTileR;
					if (panel.selectedTileR == air) {
						testEmptyRows = true;
					}
				}
				removeEmpty();
				unsavedChanges = true;
			}
		}
	} else {
 		if (!win) { //don't draw player if in win mode
			if (player.recovering%24 >= 0 && player.recovering%24 < 12) {
				spr_player.setPosition(player.tempx, player.tempy);
				switch (player.facing) {
					case up:    spr_player.setRotation(180); break;
					case down:  spr_player.setRotation(0);   break;
					case left:  spr_player.setRotation(90);  break;
					case right: spr_player.setRotation(270); break;
				}
				window.draw(spr_player);
			}
			if (player.recovering > 0) {
				player.recovering++;
				if (player.recovering >= 240) {
					player.recovering = 0;
				}
			}
		}

			sf::Listener::setPosition(sf::Vector3f(player.tempx, 0.0f, player.tempy));

		manageQueue(que_blade);
		manageQueue(que_bullet_launch);
		manageQueue(que_coin);
		manageQueue(que_breakableBlock);
	}

	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	//this manages the UI code that doesn't move with the player/scrolling
	//which is menubar and panel for edit mode, coin counter for play mode, and pause button for both

	if (editMode) {
		panel.draw(window);
		menubar.draw(window);

		if (menubar.clicked == "FILE->NEW") {
			newStage();
		} else if (menubar.clicked == "FILE->OPEN...") {
			open();
		} else if (menubar.clicked == "FILE->SAVE") {
			save();
		} else if (menubar.clicked == "FILE->SAVE AS...") {
			saveAs();
		}
	} else {
		txt_coins.setString("@" + std::to_string(player.coins));
		txt_coins.setOrigin(txt_coins.getGlobalBounds().width/2, 0);
		txt_coins.setPosition(window.getSize().x/2, 10);
		window.draw(txt_coins);
	}

	spr_pause.setPosition(window.getSize().x, 0);
	window.draw(spr_pause);

	if (win) { //if you win, draw winning box
		const uint barHeight = 16;
		if (barTimer%10 < 5) {
			bars.setPosition(0, 0);
		} else {
			bars.setPosition(0, barHeight);
		}
		barTimer++;
		bars.setSize(sf::Vector2f(window.getSize().x, barHeight));
		for (size_t i = 0; i < window.getSize().y/(barHeight*2); i++) {
			window.draw(bars);
			bars.move(0, barHeight*2);
		}
		sf::RectangleShape background;
		background.setFillColor(sf::Color(255, 255, 0));
		background.setSize(sf::Vector2f(150, 28));
		background.setOrigin(background.getSize().x/2, background.getSize().y/2);
		background.setPosition(window.getSize().x/2, window.getSize().y/2);
		window.draw(background);
		txt_you_win.setString("YOU WIN!");
		txt_you_win.setOrigin(txt_you_win.getGlobalBounds().width/2, txt_you_win.getGlobalBounds().height/2);
		txt_you_win.setPosition(window.getSize().x/2, window.getSize().y/2);
		window.draw(txt_you_win);
		if (mouse(Left) || key(Escape)) {
			killPlayer();
		}
	}
}