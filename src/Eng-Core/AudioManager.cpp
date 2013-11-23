#include "AudioManager.h"

using namespace std;

AudioManager::AudioManager(){};	
std::map <string, AudioContainer*> audioFiles;

AudioContainer* AudioManager::getAudioFile(string name){
	AudioContainer* container;
	try {
		container = audioFiles.at(name);
	} 
	catch (const exception &exc) {
		writeToLogger("Audio file " + name + " has not been set");
		return NULL;
	}
	return container;
}

void AudioManager::setAudioFile(AudioContainer* newContainer){
	audioFiles[newContainer->getFileName()] = newContainer;
}

//Helper method to write to logger
void AudioManager::writeToLogger (string message){
	Logger* logger;
	logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog(message);
}

