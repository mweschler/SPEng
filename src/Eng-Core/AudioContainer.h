#include <fstream>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Asset.h"
#include "Logger.h"

class AudioContainer : public Asset
{
private:
	sf::Music music;
	float durationOfAudioFile;
	//Internal Helper method to write to logger
	void writeToLogger (std::string message);

public:
	bool virtual load(std::string fileName);
	//Returns audio file length in seconds
	float getDuration();
	AudioContainer();
	bool virtual isPlaying();
	void virtual play();
	void virtual stop();
	void virtual pause();
	//Plays a looped audio file
	void virtual loop();
	//Assumes audio file is playing already and fades it in a designated amount of seconds
	void virtual fade(float numberOfSeconds); 
};