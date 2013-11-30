#include <iostream>
#include "gtest/gtest.h"
#include <SFML/Audio.hpp>
#include <window.h>
#include "AudioManager.h"
#include "AssetManager.h"

static AudioManager* audioManager = new AudioManager();
static AssetManager &assetMgr = *AssetManager::Instance();

TEST(AudioSuite, DISABLED_playingFunctionalitySubsytemTest){
	//AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	assetMgr.loadAsset<AudioContainer>("gunshot.wav")->play();
	//audioManager->setAudioFile(audioContainer);
	//audioManager->getAudioFile("gunshot.wav")->play();
}

TEST(AudioSuite, DISABLED_loopingFunctionalitySubsytemTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioManager->setAudioFile(audioContainer);
	audioManager->getAudioFile("gunshot.wav")->loop();
}

TEST(AudioSuite, DISABLED_fadingFunctionalitySubsytemTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioManager->setAudioFile(audioContainer);
	audioManager->getAudioFile("throughthefireandtheflames.ogg")->play();
	audioManager->getAudioFile("throughthefireandtheflames.ogg")->fade(4);
}

TEST(AudioSuite, DISABLED_gettingAudioFileDurationUnitTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->getDuration();
}

TEST(AudioSuite, DISABLED_playingFunctionalityUnitTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioContainer->play();
}

TEST(AudioSuite, DISABLED_loopingFunctionalityUnitTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioContainer->loop();
}

TEST(AudioSuite, DISABLED_fadingFunctionalityUnitTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->play();
	audioContainer->fade(4);
}

TEST(AudioSuite, DISABLED_fadingWhileNotPlayingUnitTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->fade(4);
}

// The tests below are testing the SFML library 
TEST(AudioSuite, DISABLED_playingSoundLibraryTest){
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 
	std::cout<<"Press enter to continue";
	sound.play();
	std::cin.ignore();
}

TEST(AudioSuite, DISABLED_playingMusicLibraryTest){
	sf::Music music;
	if (!music.openFromFile("throughthefireandtheflames.ogg"))
		ASSERT_DEATH(NULL,NULL); // error
	std::cout<<"Press enter to stop music and proceed";
	music.play();
	std::cin.ignore();
}

TEST(AudioSuite, DISABLED_loopingSoundLibraryTest){
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 
	std::cout<<"Press enter to end sound loop and proceed";
	sound.play();
	sound.setLoop(true);
	std::cin.ignore();
}

TEST(AudioSuite, DISABLED_fadingMusicTestLibraryTest){
	sf::Music music;
	if (!music.openFromFile("throughthefireandtheflames.ogg"))
		ASSERT_DEATH(NULL,NULL); // error
	std::cout<<"Press enter to stop fading and proceed";
	music.play();
	//Start fading
	for (int i = 99; i>=0; i--)
	{
		Sleep(150);
		music.setVolume(i);
	}
	std::cin.ignore();
}

