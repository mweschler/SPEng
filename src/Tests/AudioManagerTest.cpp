#include <iostream>
#include "gtest/gtest.h"
#include "AudioManager.h"
#include <SFML/Audio.hpp>
#include "AudioContainer.h"
#include <Windows.h>

TEST(AudioSuite, DISABLED_playingSoundTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioContainer->play();
}

TEST(AudioSuite, DISABLED_playingMusicTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->play();
}

TEST(AudioSuite, DISABLED_loopingSoundTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioContainer->loop();
}

TEST(AudioSuite, DISABLED_loopingMusicTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->loop();
}

TEST(AudioSuite, DISABLED_fadingSoundTest){
	AudioContainer* audioContainer = new AudioContainer("gunshot.wav");
	audioContainer->play();
	audioContainer->fade(1);
}

TEST(AudioSuite, DISABLED_fadingMusicTest){
	AudioContainer* audioContainer = new AudioContainer("throughthefireandtheflames.ogg");
	audioContainer->play();
	audioContainer->fade(4);
}

TEST(AudioSuite, DISABLED_fadingSoundLibraryTest){
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

