#include <string>
#include <fstream>
#include <iostream>
#include "AudioContainer.h"
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "logger.h"
#include <sstream>
using namespace std;
		
		string fileName;
		sf::Music music;
		float duration;
		Logger* logger = Logger::Instance();

		AudioContainer::AudioContainer(string nameOfAudioFile)
		{
			fileName = nameOfAudioFile;
			logger->initialize();		
			load();
		}

		string AudioContainer::getFileName()
		{
			return fileName;
		}

		float AudioContainer::getDuration()
		{
			std::ostringstream buff;
			buff<<duration;
			return duration;
		}

		bool AudioContainer::load()
		{
			bool success = true;
			if (!music.openFromFile(fileName)){
				logger->writeToLog("Failed to open audio file");
				success = false;
			}			
			//Initialize length of audio file
			sf::Time length = music.getDuration();
			duration = length.asSeconds();
			return success;
		}

		void AudioContainer::play(){
			music.play();
		}

		void AudioContainer::pause(){
			music.pause();
		}

		void AudioContainer::stop(){
			music.stop();
		}

		void AudioContainer::loop(){
			music.setLoop(true);
			music.play();
		}

		void AudioContainer::fade(float numberOfSeconds)
		{
			if(music.getStatus() == music.Playing){
				float sleepTime = numberOfSeconds * 15;
				for (int i = 99; i>=0; i--)
				{					
					music.setVolume(i);
					Sleep(sleepTime);
				}
				music.stop();	
			}
			else{
				logger->writeToLog("Cannot fade audio file because it is not currently playing");
			}
		}
