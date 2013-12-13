#include "gtest/gtest.h"
#include "InputHandler.h"
#include <SFML/Audio.hpp>
#include <windows.h>
#include <conio.h>
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


	UserInput input;
	sf::Joystick::update();

	bool connected = sf::Joystick::isConnected(0);
	unsigned int buttons = sf::Joystick::getButtonCount(0);
	std::cout << buttons;


	bool flag = true;

	while(flag)
	{
		sf::Joystick::update();
		

		//Button 2 is X
		if (input.isJoystickButtonPressed(0, 2))
		{
			printf("Make my ass Reload\n");
			soundReload.play();
			_sleep(100);

		}

		//Right Stick Pressed in
		if (input.isJoystickButtonPressed(0, 9))
		{
			
		}
		//Button 1 is B
		if(input.isJoystickButtonPressed(0,1))
		{

			printf("Player Crouchs\n");
			
			_sleep(100);


		}
		//Y button is 3
		if(input.isJoystickButtonPressed(0,3))
		{

			printf("Change Weapon\n");
			_sleep(100);


		}


		//Button 4 is Left Bumper
		if(input.isJoystickButtonPressed(0,4))
		{

			printf("Melee\n");
			_sleep(100);


		}

		//This is A button
			if(input.isJoystickButtonPressed(0,0))
		{

			printf("Player Jumps\n");
			soundJump.play();
			_sleep(100);


		}



		//POV IS D PAD
		float posOfLeftY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		float posOfLeftX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float posOfRightX = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
		float posOfRightY = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
		float Triggers = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);


		if(posOfLeftY >=40 )
		{


			printf("Move Person Down\n");
			
		}

		if(posOfLeftY <= -40 )
		{


			printf("Move Person UP\n");
		
		}


		if(posOfLeftX >=40 )
		{


			printf("Move Person Right\n");
			
		}

		
		if(posOfRightX >=40 )
		{


			printf("Aim Down\n");
			
		}


		
		if(posOfRightX <=-40 )
		{


			printf("Aim Up\n");
			
		}

		if(posOfRightY <=-40 )
		{


			printf("Aim left\n");
			
		}

		if(posOfRightY >=40 )
		{


			printf("Aim Right\n");
			
		}

		if(posOfLeftX <= -40 )
		{


			printf("Move Person Left\n");
		
		}

			if(Triggers >= 40 )
		{

			_sleep(100);
			printf("Zoom In\n");
		
		}

		if(Triggers <=-40)
		{

			printf("Shoot Gun!\n");
			sound.play();
			_sleep(100);


		}

		
		if (input.isKeyPressed(sf::Keyboard::Escape))
		{
			flag = false;

		}

	}


	
	ASSERT_EQ(true,	connected);
//	ASSERT_EQ(200, mousePos.y);


}

//This will be joystick test
TEST(userInputTest, test_six)
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

	
	UserInput input;
	sf::Joystick::update();

	bool connected = sf::Joystick::isConnected(0);
	unsigned int buttons = sf::Joystick::getButtonCount(0);
	std::cout << buttons;


	bool flag = true;


		


	while(flag)
	{
		sf::Joystick::update();
		

		//Button 2 is X
		if (input.isJoystickButtonPressed(0, 2))
		{
			printf("X button is Pressed\n");
			soundReload.play();
			_sleep(100);

		}

		//Right Stick Pressed in
		if (input.isJoystickButtonPressed(0, 9))
		{
			
		}
		//Button 1 is B
		if(input.isJoystickButtonPressed(0,1))
		{

			printf("B Button is Pressed\n");
			
			_sleep(100);


		}

		//Y button is 3
		if(input.isJoystickButtonPressed(0,3))
		{

			printf("Y button is pressed\n");
			_sleep(100);


		}


		//Button 4 is Left Bumper
		if(input.isJoystickButtonPressed(0,4))
		{

			printf("Left Bumper Is Pressed\n");
			_sleep(100);


		}

		//This is A button
			if(input.isJoystickButtonPressed(0,0))
		{

			printf("A Button is Pressed\n");
			soundJump.play();
			_sleep(100);


		}


		//POV IS D PAD
		float posOfLeftY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		float posOfLeftX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float posOfRightX = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
		float posOfRightY = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
		float Triggers = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	





	
		sf::Vector2i mousePos = input.getMousePosition();


		if(posOfLeftY >=40 )
		{


			input.setMousePostion(mousePos.x,mousePos.y + 1);
			//printf("Left Stick moved up");
			_sleep(0.5);
			
		}

		
		if(posOfLeftY <= -40 )
		{

			input.setMousePostion(mousePos.x,mousePos.y -1);
			_sleep(1);
		
		}
		sf::Joystick::update();

		//Move Right
		if(posOfLeftX >=40 )
		{


			input.setMousePostion(mousePos.x +1,mousePos.y);
				_sleep(0.5);
		}

		//Move Right
		if(posOfLeftX <= -40 )
		{


			input.setMousePostion(mousePos.x -1,mousePos.y);
				_sleep(0.5);
		
		}

		//Move Diagonally bottom left
		if(posOfLeftX <= -40 && posOfLeftY >=40)
		{
			input.setMousePostion(mousePos.x -2,mousePos.y +2);

			_sleep(0.5);
		}

		//Move Diagonally bottom Right
		if(posOfLeftX >=40 && posOfLeftY >=40)
		{
			input.setMousePostion(mousePos.x +2,mousePos.y +2);

			_sleep(0.5);
		}

		//Move Diagonally Top Right
		if(posOfLeftX >=40 && posOfLeftY <= -40)
		{
			input.setMousePostion(mousePos.x +2,mousePos.y -2);

			_sleep(0.5);
		}

		//Move Diagonally Top Left
		if(posOfLeftX <=-40 && posOfLeftY <= -40)
		{
			input.setMousePostion(mousePos.x -2,mousePos.y -2);

			_sleep(0.5);
		}
		
		if(posOfRightX <=-40 )
		{


			printf("Right Stick Moved Up\n");
			
		}

		sf::Joystick::update();
		if(posOfRightY <=-40 )
		{


			printf("Right Stick Moved Left\n");
			
		}

		if(posOfRightY >=40 )
		{


			printf("Right Stick Moved Right\n");
			
		}

		

			if(Triggers >= 40 )
		{

			_sleep(100);
			printf("Left Trigger Pressed\n");
		
		}

		if(Triggers <=-40)
		{
				printf("Right Trigger Pressed\n");
			sound.play();
			_sleep(100);

		   


		}


		
		if (input.isKeyPressed(sf::Keyboard::Escape))
		{
			flag = false;

		}

	}


	
	ASSERT_EQ(true,	connected);
//	ASSERT_EQ(200, mousePos.y);


}