#ifndef COL_NONE

#define COL_NONE    sf::Color(0, 0, 0) //black
#define COL_LOW     sf::Color(214, 0, 255) //magenta
#define COL_LOWMED  sf::Color(235, 123, 128) //halfway between magenta and yellow
#define COL_MED     sf::Color(255, 246, 1) //yellow
#define COL_LOWHIGH sf::Color(0xA0, 0xA0, 0xA0) //grey
#define COL_HIGH    sf::Color(62, 255, 209) //light blue

#define COL_TILE_NORMAL      sf::Color(tile.getColor().r, tile.getColor().g, tile.getColor().b, 255)
#define COL_TILE_TRANSLUCENT sf::Color(tile.getColor().r, tile.getColor().g, tile.getColor().b, 0xA0)

#define COL_NORMAL      sf::Color(255, 255, 255, 0)
#define COL_TRANSPARENT sf::Color(255, 255, 255, 0)

// #define COL_NONE sf::Color(0, 0, 0)
// #define COL_LOW sf::Color(255, 0, 255)
// #define COL_MED sf::Color(255, 255, 0)
// #define COL_HIGH sf::Color(255, 255, 255)

#endif