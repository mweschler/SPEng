#include <map>
#include "AudioContainer.h"

using namespace std;

class AudioManager 
{
private:
	std::map <string, AudioContainer*> audioFiles;

public:
	//Helper method to write to logger
	void writeToLogger (string message);
	AudioManager();	
	AudioContainer* getAudioFile(string name);
	void setAudioFile(AudioContainer* newContainer);
};