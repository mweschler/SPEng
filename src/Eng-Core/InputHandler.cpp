#include "InputHandler.h"


//Gets current postion of mouse.
sf::Vector2i UserInput::getMousePosition()
{
	
	
	return sf::Mouse::getPosition();


}
//Returns true if a key is pressed.
bool UserInput::isKeyPressed(enum sf::Keyboard::Key theKey)
{
	
	return	 (sf::Keyboard::isKeyPressed(theKey));

};

//Returns true if a mouse betton is pressed.
bool UserInput::isMouseKeyPressed(enum sf::Mouse::Button theButton)
{

	return (sf::Mouse::isButtonPressed(theButton ));
};

//Returns true of Joystick Button is pressed
bool UserInput::isJoystickButtonPressed(int joystick, int button)
{


	return sf::Joystick::isButtonPressed(joystick,button);
}

//Set the postion of the mouse
void UserInput::setMousePostion(int x, int y)
{

sf::Mouse::setPosition(sf::Vector2i(x, y));
}

