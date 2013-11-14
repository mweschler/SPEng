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


	sf::SoundBuffer bufferJump;
	sf::Sound soundJump;
	bufferJump.loadFromFile("jump.wav");
	soundJump.setBuffer(bufferJump);

	sf::SoundBuffer bufferReload;
	sf::Sound soundReload;
	bufferReload.loadFromFile("reload.wav");
	soundReload.setBuffer(bufferReload);

	sf::SoundBuffer bufferHadoken;
	sf::Sound soundHadoken;
	bufferHadoken.loadFromFile("hadoken.wav");
	soundHadoken.setBuffer(bufferHadoken);



	bool flag = true;

	UserInput input;
	while(flag)
	{
		_sleep(4);
		if (input.isKeyPressed(sf::Keyboard::A))
		{
			printf("Move Character Left\n");

		}


		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::Space))
		{
			printf("Make Character Jump\n");
			soundJump.play();

		}
		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::W))
		{

			printf("Move Character Forward\n");


		}


		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::D))
		{

			printf("Move Character Right\n");


		}
		_sleep(4);
		if(input.isMouseKeyPressed(sf::Mouse::Left))
		{
			printf("GUN SHOT!!!!\n");

			sound.play();


		}

		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::S))
		{

			printf("Move Character Downward\n");


		}


		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::R))
		{

			printf("Reload Weapon\n");
			soundReload.play();

		}


		_sleep(4);
		if(input.isKeyPressed(sf::Keyboard::H) && input.isKeyPressed(sf::Keyboard::J))
		{

			printf("Hadoken!!!\n");
			soundHadoken.play();

		}


		_sleep(4);
		if (input.isKeyPressed(sf::Keyboard::Escape))
		{
			flag = false;
		}
	}





		
	
	ASSERT_EQ(true, true);


}

//This is a mouse postion test
TEST(userInputTest, DISABLED_test_four)
{
	UserInput input;
bool flag = true;

while(flag)
{
sf::Vector2i mousePos = input.getMousePosition();
_sleep(10);
printf("X: %d Y: %d\n",mousePos.x,mousePos.y);
if(input.isKeyPressed(sf::Keyboard::Escape))
{
	flag = false;

}
ASSERT_EQ(true, true);

};
	

	
	
//	ASSERT_EQ(10,	mousePos.x);
//	ASSERT_EQ(200, mousePos.y);


}

//This will be joystick test
TEST(userInputTest, DISABLED_test_five)
{
	UserInput input;
	sf::Joystick::update();

	bool connected = sf::Joystick::isConnected(0);
	unsigned int buttons = sf::Joystick::getButtonCount(0);
	std::cout << buttons;


	bool flag = true;

	while(flag)
	{
		sf::Joystick::update();
		_sleep(50);
		if (sf::Joystick::isButtonPressed(0, 2))
		{
			printf("Make my ass Reload\n");

		}





		_sleep(4);
		if (input.isKeyPressed(sf::Keyboard::Escape))
		{
			flag = false;

		}

	}


	
	ASSERT_EQ(true,	connected);
//	ASSERT_EQ(200, mousePos.y);


}