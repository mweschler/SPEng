#include "gtest/gtest.h"
#include "InputHandler.h"
#include "AudioManager.h"
#include <SFML/Audio.hpp>

//If this test gives you an error. It means you were pressing up
TEST(userInputTest, DISABLED_test_one)
{
	UserInput input;

	bool test =input.isKeyPressed(sf::Keyboard::Up);
	input.isKeyPressed(sf::Keyboard::Up);
	ASSERT_EQ(false,	test);


}

//Test to make sure the mouse was moved into the correct postion.
//This test also makes sure get mouse postion is working correctly.
TEST(userInputTest, DISABLED_test_two)
{
	UserInput input;
	
	
	input.setMousePostion(10,20);

	sf::Vector2i mousePos = input.getMousePosition();
	
	ASSERT_EQ(10,	mousePos.x);
//	ASSERT_EQ(200, mousePos.y);


}

//Testing The User Input Engine with sound and Actions.
TEST(userInputTest, DISABLED_test_three)
{

	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile("gunshot.wav"))
		ASSERT_DEATH(NULL,NULL); // error
	sound.setBuffer(buffer); 


	//sf::SoundBuffer bufferJump;
//	sf::Sound soundJump;
	//bufferJump.loadFromFile("jump.wav");
	//soundJump.setBuffer(bufferJump);


	bool flag = true;

	UserInput input;
	while(flag)
	{
		_sleep(12);
		if (input.isKeyPressed(sf::Keyboard::A))
		{
			printf("Move Character Left\n");

		}


		_sleep(12);
		if(input.isKeyPressed(sf::Keyboard::Space))
		{
			printf("Make Character Jump\n");
		//	soundJump.play();

		}
		_sleep(12);
		if(input.isKeyPressed(sf::Keyboard::W))
		{

			printf("Move Character Forward\n");


		}


		_sleep(12);
		if(input.isKeyPressed(sf::Keyboard::D))
		{

			printf("Move Character Right\n");


		}
		_sleep(12);
		if(input.isMouseKeyPressed(sf::Mouse::Left))
		{
			printf("GUN SHOT!!!!\n");

			sound.play();


		}

		_sleep(12);
		if(input.isKeyPressed(sf::Keyboard::S))
		{

			printf("Move Character Downward\n");


		}


		_sleep(12);
		if(input.isKeyPressed(sf::Keyboard::R))
		{

			printf("Reload Weapon\n");


		}


		_sleep(12);
		if (input.isKeyPressed(sf::Keyboard::Escape))
		{
			flag = false;
		}	
	}





		
	
	ASSERT_EQ(true, true);


}