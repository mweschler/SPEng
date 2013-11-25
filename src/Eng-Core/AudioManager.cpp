#include "AudioManager.h"

using namespace std;

AudioManager::AudioManager(){};	
std::map <string, AudioContainer*> audioFiles;

// Retrieves an audio file from the map with the given name.
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

// Sets an audio file from the map with the given name.
void AudioManager::setAudioFile(AudioContainer* newContainer){
	audioFiles[newContainer->getFileName()] = newContainer;
}

// Removes an audio file from the map with the given name.
template <typename T> void removeAudioFile(string name) {
	int result = audioFiles.erase(name);
	if (result == 0) {
		writeToLogger("Cannot remove audio file " + name + " because it does not exist");
	}
}

void AudioManager::writeToLogger (string message){
	Logger* logger;
	logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog(message);
}

