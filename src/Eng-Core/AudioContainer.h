#include <fstream>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Asset.h"
#include "Logger.h"

using namespace std;

class AudioContainer : public Asset
{
private:
	std::string fileName;	
	sf::Music music;
	float durationOfAudioFile;
	bool virtual load();
	//Helper method to write to logger
	void writeToLogger (string message);

public:
	std::string getFileName();
	//Returns audio file length in seconds
	float getDuration();
	AudioContainer(std::string name);
	bool virtual isPlaying();
	void virtual play();
	void virtual stop();
	void virtual pause();
	//Plays a looped audio file
	void virtual loop();
	//Assumes audio file is playing already and fades it in a designated amount of seconds
	void virtual fade(float numberOfSeconds); 
};