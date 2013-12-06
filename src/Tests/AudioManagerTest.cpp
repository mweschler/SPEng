#include <iostream>
#include "gtest/gtest.h"
#include <SFML/Audio.hpp>
#include <window.h>
#include "AudioContainer.h"
#include "AssetManager.h"

static AssetManager &assetMgr = *AssetManager::Instance(); 

//If I declare this line here and erase the two next declarations of gunshot it works
//AudioContainer* gunShot = (AudioContainer*)assetMgr.loadAsset<AudioContainer>("gunshot.wav");
//So I'm thinking there could be something wrong with what it is returning when the user tries to load the asset a second time. 

TEST(AudioSuite, playingFunctionalitySystemTest){
	AudioContainer* gunShot = (AudioContainer*)assetMgr.loadAsset<AudioContainer>("gunshot.wav");
	gunShot->play();
	Sleep(5000);
}

TEST(AudioSuite, playingAgainFunctionalitySystemTest){
	AudioContainer* gunShot = (AudioContainer*)assetMgr.loadAsset<AudioContainer>("gunshot.wav");
	gunShot->play();
}

/*
TEST(AudioSuite, fadingFunctionalitySystemTest){
	AudioContainer* finalBossBattleMusic = (AudioContainer*)assetMgr.loadAsset<AudioContainer>("throughthefireandtheflames.ogg");
	finalBossBattleMusic->play();
	finalBossBattleMusic->fade(4);
}

TEST(AudioSuite, gettingAudioFileDurationSubSystemTest){
	AudioContainer* audioContainer = new AudioContainer();
	audioContainer->load("throughthefireandtheflames.ogg");
	audioContainer->getDuration();
}

TEST(AudioSuite, playingFunctionalitySubSystemTest){
	AudioContainer* audioContainer = new AudioContainer();
	audioContainer->load("gunshot.wav");
	audioContainer->play();
}

TEST(AudioSuite, loopingFunctionalitySubSystemTest){
	AudioContainer* audioContainer = new AudioContainer();
	audioContainer->load("gunshot.wav");
	audioContainer->loop();
}

TEST(AudioSuite, fadingFunctionalitySubSystemTest){
	AudioContainer* audioContainer = new AudioContainer();
	audioContainer->load("throughthefireandtheflames.ogg");
	audioContainer->play();
	audioContainer->fade(4);
}

TEST(AudioSuite, fadingWhileNotPlayingSubSystemTest){
	AudioContainer* audioContainer = new AudioContainer();
	audioContainer->load("throughthefireandtheflames.ogg");
	audioContainer->fade(4);
}

// The tests below are testing successful integration of the SFML library 
TEST(AudioSuite, playingSoundLibraryTest){
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 
	std::cout<<"Press enter to continue";
	sound.play();
	std::cin.ignore();
}

TEST(AudioSuite, playingMusicLibraryTest){
	sf::Music music;
	if (!music.openFromFile("throughthefireandtheflames.ogg"))
		ASSERT_DEATH(NULL,NULL); // error
	std::cout<<"Press enter to stop music and proceed";
	music.play();
	std::cin.ignore();
}

TEST(AudioSuite, loopingSoundLibraryTest){
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

TEST(AudioSuite, fadingMusicTestLibraryTest){
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
}*/

