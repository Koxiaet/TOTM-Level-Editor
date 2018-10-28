#include "soundGenerator.hpp"
#include <cmath>

sf::SoundBuffer squareWave(uint pitch, sf::Int16 length, sf::Int16 volume)
{
	double intpart; //a temporary variable, ignore
	while (modf((44100.0/(double)pitch)/2.0, &intpart) != 0.0) { //while isn't an integer
		pitch++;
	}
	uint wavelength = 44100/pitch;

	sf::Int16* samples;
	samples = new sf::Int16[wavelength*length];

	for (uint waveCounter = 0; waveCounter < (uint)length; waveCounter++) {
		for (uint i = 0; i < wavelength/2; i++) {
			samples[waveCounter*wavelength + i] = volume;
		}
		for (uint i = wavelength/2; i < wavelength; i++) {
			samples[waveCounter*wavelength + i] = -volume;
		}
	}

	sf::SoundBuffer b;
	b.loadFromSamples(samples, wavelength*length, 1, 44100);
	delete [] samples;
	return b;
}

sf::SoundBuffer blinkingSquareWave(uint pitch, sf::Int16 length, sf::Int16 volume, uint blinkStart, uint blinkStop)
{
	double intpart; //a temporary variable, ignore
	while (modf((44100.0/(double)pitch)/2.0, &intpart) != 0.0) { //while isn't an integer
		pitch++;
	}
	uint wavelength = 44100/pitch; //not 420 :'(

	sf::Int16* samples;
	samples = new sf::Int16[wavelength*length];

	for (uint waveCounter = 0; waveCounter < (uint)length; waveCounter++) {
		if (waveCounter < blinkStart || waveCounter > blinkStop) {
			for (uint i = 0; i < wavelength/2; i++) {
				samples[waveCounter*wavelength + i] = volume;
			}
			for (uint i = wavelength/2; i < wavelength; i++) {
				samples[waveCounter*wavelength + i] = -volume;
			}
		}
	}

	sf::SoundBuffer b;
	b.loadFromSamples(samples, wavelength*length, 1, 44100);
	delete [] samples;
	return b;
}

sf::SoundBuffer fallingSquareWave(uint pitchBegin, uint pitchEnd, uint fallSpeed, sf::Int16 volume)
{
	std::vector<sf::Int16> samples;

	for (uint waveCounter = pitchBegin; waveCounter > pitchEnd; waveCounter -= fallSpeed) {
		for (uint i = 0; i < 44100/waveCounter; i++) {
			samples.push_back(volume);
		}
		for (uint i = 0; i < 44100/waveCounter; i++) {
			samples.push_back(-volume);
		}
	}

	sf::SoundBuffer b;
	b.loadFromSamples(&samples[0], samples.size(), 1, 44100);
	return b;
}

sf::SoundBuffer risingSquareWave(uint pitchBegin, uint pitchEnd, uint riseSpeed, sf::Int16 volume)
{
	std::vector<sf::Int16> samples;

	for (uint waveCounter = pitchBegin; waveCounter < pitchEnd; waveCounter += riseSpeed) {
		for (uint i = 0; i < 44100/waveCounter; i++) {
			samples.push_back(volume);
		}
		for (uint i = 0; i < 44100/waveCounter; i++) {
			samples.push_back(-volume);
		}
	}

	sf::SoundBuffer b;
	b.loadFromSamples(&samples[0], samples.size(), 1, 44100);
	return b;
}

sf::SoundBuffer dimSquareWave(uint pitch, sf::Int16 length, sf::Int16 volumeStart, sf::Int16 volumeChange) //diminuendo
{
	double intpart; //a temporary variable, ignore
	while (modf((44100.0/(double)pitch)/2.0, &intpart) != 0.0) { //while isn't an integer
		pitch++;
	}
	uint wavelength = 44100/pitch;

	sf::Int16* samples;
	samples = new sf::Int16[wavelength*length];

	for (uint waveCounter = 0; waveCounter < (uint)length; waveCounter++) {
		for (uint i = 0; i < wavelength/2; i++) {
			samples[waveCounter*wavelength + i] = volumeStart;
		}
		for (uint i = wavelength/2; i < wavelength; i++) {
			samples[waveCounter*wavelength + i] = -volumeStart;
		}
		volumeStart -= volumeChange;
	}

	sf::SoundBuffer b;
	b.loadFromSamples(samples, wavelength*length, 1, 44100);
	delete [] samples;
	return b;
}

sf::SoundBuffer crescSquareWave(uint pitch, sf::Int16 length, sf::Int16 volumeStart, sf::Int16 volumeChange) //crescendo
{
	double intpart; //a temporary variable, ignore
	while (modf((44100.0/(double)pitch)/2.0, &intpart) != 0.0) { //while isn't an integer
		pitch++;
	}
	uint wavelength = 44100/pitch;

	sf::Int16* samples;
	samples = new sf::Int16[wavelength*length];

	for (uint waveCounter = 0; waveCounter < (uint)length; waveCounter++) {
		for (uint i = 0; i < wavelength/2; i++) {
			samples[waveCounter*wavelength + i] = volumeStart;
		}
		for (uint i = wavelength/2; i < wavelength; i++) {
			samples[waveCounter*wavelength + i] = -volumeStart;
		}
		volumeStart += volumeChange;
	}

	sf::SoundBuffer b;
	b.loadFromSamples(samples, wavelength*length, 1, 44100);
	delete [] samples;
	return b;
}