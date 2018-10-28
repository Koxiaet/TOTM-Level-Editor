#include <SFML/Audio.hpp>

#ifndef __KAI__TOTM__SOUNDGENERATOR__
#define __KAI__TOTM__SOUNDGENERATOR__ 1

sf::SoundBuffer squareWave(uint pitch, sf::Int16 length, sf::Int16 volume);
sf::SoundBuffer blinkingSquareWave(uint pitch, sf::Int16 length, sf::Int16 volume, uint blinkStart, uint blinkStop);
sf::SoundBuffer fallingSquareWave(uint pitchBegin, uint pitchEnd, uint fallSpeed, sf::Int16 volume);
sf::SoundBuffer risingSquareWave(uint pitchBegin, uint pitchEnd, uint riseSpeed, sf::Int16 volume);
sf::SoundBuffer dimSquareWave(uint pitch, sf::Int16 length, sf::Int16 volumeStart, sf::Int16 volumeChange); //diminduendo
sf::SoundBuffer crescSquareWave(uint pitch, sf::Int16 length, sf::Int16 volumeStart, sf::Int16 volumeChange); //crescendo

#endif