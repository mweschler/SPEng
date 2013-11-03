#include <iostream>
#include "gtest/gtest.h"
#include "AudioManager.h"
#include <SFML/Audio.hpp>
#include <Windows.h>

TEST(AudioSuite, DISABLED_playingSoundTest){
	int result = 4;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 
	std::cout<<"Press enter to proceed";
	sound.play();
	std::cin.ignore();
	EXPECT_EQ(4,result);
}

TEST(AudioSuite, DISABLED_playingMusicTest){
	int result = 4;
	sf::Music music;
	if (!music.openFromFile("throughthefireandtheflames.ogg"))
		ASSERT_DEATH(NULL,NULL); // error
	std::cout<<"Press enter to stop music and proceed";
	music.play();
	std::cin.ignore();
	EXPECT_EQ(4,result);
}

TEST(AudioSuite, DISABLED_loopingSound){
	int result = 4;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 
	std::cout<<"Press enter to end sound loop and proceed";
	sound.play();
	sound.setLoop(true);
	std::cin.ignore();
	EXPECT_EQ(4,result);
}

TEST(AudioSuite, DISABLED_fadingMusicTest){
	int result = 4;
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
	EXPECT_EQ(4,result);
}

