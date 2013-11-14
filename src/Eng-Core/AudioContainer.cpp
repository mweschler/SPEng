#include <string>
#include <fstream>
#include <iostream>
#include "AudioContainer.h"
#include <SFML/Audio.hpp>
#include <Windows.h>
using namespace std;

		string fileName;
		sf::Music music;
		float duration;

		AudioContainer::AudioContainer(string nameOfAudioFile)
		{
			fileName = nameOfAudioFile;
			load();
		}

		string AudioContainer::getFileName()
		{
			return fileName;
		}

		float AudioContainer::getDuration()
		{
			return duration;
		}

		bool AudioContainer::load()
		{
			bool success = true;
			if (!music.openFromFile(fileName)){
				// Log the error here
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
			if(music.Playing){
				music.pause();
			}
			else{
				//Audio file is not currently playing
			}
		}

		void AudioContainer::stop(){
			if(music.Playing){
				music.stop();
			}
			else{
				//Audio file is not currently playing
			}
		}

		void AudioContainer::loop(){
			music.setLoop(true);
			music.play();
		}

		void AudioContainer::fade(float numberOfSeconds)
		{
			float sleepTime = numberOfSeconds * 15;
			for (int i = 99; i>=0; i--)
			{					
				music.setVolume(i);
				Sleep(sleepTime);
			}
			music.stop();		
		}

		bool AudioContainer::release(AudioContainer asset)
		{
			cout << "Release it\n";
			return true;
		}
