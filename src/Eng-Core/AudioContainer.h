#include <fstream>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Asset.h"
#include "Logger.h"

/*! An AudioContainer for use in audio playback
*/
class AudioContainer : public Asset
{
private:
	sf::Music music;
	float durationOfAudioFile;
	void writeToLogger (std::string message);
public:
	/*! Default constructor for Audio Container class
	*/
	AudioContainer();
	/*! Loads the audioFile to main memory, inherited from asset
		\param fileName File name of audio file
	*/
	bool virtual load(std::string fileName);
	/*! Returns the length of the audio file in seconds
	*/
	float getDuration();
	/*! Returns whether or not the audio file is currently playing
		\return true if audio file is currently playing, false otherwise
	*/
	bool virtual isPlaying();
	/*! Plays audio file
	*/
	void virtual play();
	/*! Stops audio file
	*/
	void virtual stop();
	/*! Pauses audio file if it is currently playing
	*/
	void virtual pause();
	/*! Plays and loops an audio file until stop is called
	*/
	void virtual loop();
	/*! Fades audio file for a specified amount of seconds. If audio file is not playing, 
		it logs the error
		\param numberOfSeconds Number of seconds that the fading will last until audio 
		playback has stopped
	*/
	void virtual fade(float numberOfSeconds); 
};