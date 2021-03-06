#include "AudioContainer.h"
#include <Windows.h>
#include "AssetManager.h"

using namespace std;

AudioContainer::AudioContainer()
{
}

//Structure used to store information passed to new thread which is used when fading an audio file
struct threadData
{
	float threadNumberOfSeconds;
	sf::Music &threadMusic;
	threadData(float numberOfSecondsParam, sf::Music &musicParam) : threadNumberOfSeconds(numberOfSecondsParam), threadMusic(musicParam) {}
};

//Returns the duration of the music file
float AudioContainer::getDuration()
{
	std::ostringstream buff;
	buff<<durationOfAudioFile;
	return durationOfAudioFile;
}

//Returns if music is already playing
bool AudioContainer::isPlaying(){
	return music.getStatus() == music.Playing;
}

bool AudioContainer::load(std::string fileName)
{
	if (!music.openFromFile(fileName)){
		writeToLogger("Failed to load audio file");
		return false;
	}
	
	//Initialize length of audio file
	sf::Time length = music.getDuration();
	durationOfAudioFile = length.asSeconds();

	return true;
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

DWORD WINAPI threadFade(LPVOID lpParameter)
{
	threadData *td = (threadData*)lpParameter;
	float sleepTime = td->threadNumberOfSeconds * 15;
		for (int i = 99; i>=0; i--)
		{					
			td->threadMusic.setVolume(i);
			Sleep(sleepTime);
		}
	td->threadMusic.stop();
	return 0;
}

void AudioContainer::fade(float numberOfSeconds)
{
	if(isPlaying()){
		CreateThread(NULL, 0, threadFade, new threadData(numberOfSeconds,music) , 0, 0);			
	}
	else{
		writeToLogger("Cannot fade audio file because it is not currently playing");
	}
}

void AudioContainer::writeToLogger (string message){
	Logger* logger;
	logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog(message);
}
