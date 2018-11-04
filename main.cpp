#include "colors.hpp"

#include "game/stage.hpp"
#include "title/title.hpp"

#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "tinyfd.h"
#include "rand.hpp"

#define key(x)   sf::Keyboard::isKeyPressed(sf::Keyboard::x)
#define mouse(x) sf::Mouse::isButtonPressed(sf::Mouse::x)

enum modetype
{
	mode_title,
	mode_game,
	mode_edit
};

typedef enum modetype modetype;

int main()
{
	srand(time(NULL));
	r.reseed(time(NULL));
	chdir("/Users/riejewson/Desktop/Kai/Coding/C++/totm/app/Contents/MacOS");

	modetype mode = mode_title; //0 is title, 1 is game, 2 is edit

	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Tomb of the Mask");
	window.setFramerateLimit(60);

	stage stage;
	title titleScreen;

	bool focused = true;
	bool disableClick = true; //when the edit button is clicked, a tile (unwanted) is placed where the cursor clicked, because
	//clicks last longer than 1 frame. So, this flag is set when that button is clicked, disabling click events until
	//the cursor has been released.

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				if (stage.warnUnsavedChanges() != tinyfd_cancel) {
					window.close();
				}
			}
			if (e.type == sf::Event::LostFocus) {
				focused = false;
			}
			if (e.type == sf::Event::GainedFocus) {
				focused = true;
			}
			if (e.type == sf::Event::Resized) {
				titleScreen.resize(window);
			}
		}
		window.clear(COL_NONE);

		if (focused) {
			switch (mode) {
				case mode_title:
					switch (titleScreen.testClicked()) {
						case editButton:
							mode = mode_edit;
							disableClick = true;
							stage.changeToEditMode();
							break;
						case playButton:
							mode = mode_game;
							if (stage.changeToPlayMode() == 1) { //failed
								mode = mode_title;
							}
							break;
						case exitButton:
							if (stage.warnUnsavedChanges() != tinyfd_cancel) {
								window.close();
							}
							break;
					}

					titleScreen.draw(window);
					break;
				case mode_game:
					if (stage.pausePressed(window)) {
						mode = mode_title;
					}
					stage.controlPlayer();
					stage.draw(window);
					break;
				case mode_edit:
					if (stage.pausePressed(window)) {
						mode = mode_title;
					}
					stage.draw(window, disableClick);
					break;
			}
		}

		if (disableClick) {
			if (!mouse(Left)) {
				disableClick = false;
			}
		}

		window.display();
	}
	return 0;
}