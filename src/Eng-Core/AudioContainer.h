#pragma once
#include <String>
#include "Asset.h"
#include <SFML/Audio.hpp>

class AudioContainer : public Asset{

	public:
		std::string getFileName();
		//Returns audio file length in seconds
		float getDuration();
		AudioContainer(std::string name);
		bool virtual load();
		void virtual play();
		void virtual stop();
		void virtual pause();
		//Plays a looped audio file
		void virtual loop();
		//Assumes audio file is playing already and fades it in a designated amount of seconds
		void virtual fade(float numberOfSeconds); 
		
	private:
		std::string fileName;	
		sf::Music music;
		float duration;
};