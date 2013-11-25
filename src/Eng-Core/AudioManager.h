#include <map>
#include "AudioContainer.h"

using namespace std;

class AudioManager 
{
private:
	std::map <string, AudioContainer*> audioFiles;
	//Helper method to write to logger
	void writeToLogger (string message);

public:
	AudioManager();	
	AudioContainer* getAudioFile(string name);
	void setAudioFile(AudioContainer* newContainer);
	void removeAudioFile(string name);
};