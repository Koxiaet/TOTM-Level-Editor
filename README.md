# TOTM Level Editor

This is a port for desktop and a level editor for the mobile game Tomb of the Mask.

## Building and Executing

### Prerequisites

You must have [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) and g++ installed to compile.

### Building

run:
g++ -o TOTM title/title.cpp tinyfd.o game/stage.cpp game/soundGenerator.cpp game/player.cpp game/stage_draw.cpp game/files.cpp game/queue.cpp game/bullet.cpp edit/panel.cpp edit/menu/menuSection.cpp edit/menu/menubar.cpp edit/menu/menuItem.cpp main.cpp lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network 

This will create an executable 'TOTM', which you can execute.

## Built With

* [SFML 2.5.1](https://www.sfml-dev.org/) - The graphics library
* [tinyfiledialogs](https://sourceforge.net/projects/tinyfiledialogs/) - Native open-save dialogs, et cetera

## Stuff I Would Like to Improve

* Add animations to the sprites, and improve them in general
* More blocks
* Tools in edit mode (paint brush, select, move, rotate, et cetera)
* Music

## Authors

* **Kai Jewson**

## Acknowledgments

* Playgendary made the original game, so play it if you haven't already
