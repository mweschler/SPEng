#include <stdio.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
class UserInput
{
	
public:
		/*! Reurns true if mouse button passed is pressed
		\param type sf::Mouse:: Then button you want to check*/
		bool isMouseKeyPressed(enum sf::Mouse::Button theButton);
		/*!Returns a vector that contains the postion of the mouse as an x and y float*/
		sf::Vector2i getMousePosition();
		/*! Reurns true if key button is pressed
		\param type sf::Keyboard:: Then button you want to check*/
	 	bool isKeyPressed(enum sf::Keyboard::Key theKey);
		/*!Change the current positon of the mouse*/
	    void setMousePostion(int x, int y);
		/*! Reurns true if Joystick button passed is pressed
		\param type int joystick number
		\param type int the button on the joystick*/
		bool isJoystickButtonPressed(int joystick, int button);
		/*! Returns true if the joystick is pressed*/
		bool isJoystickConnected();
		/*! This needs to be called to get the current status of the joystick*/
		void updateStateOfJoystick();
 
};
	