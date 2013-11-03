#include <stdio.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
class UserInput
{
	
public:
		bool isMouseKeyPressed(enum sf::Mouse::Button theButton);
		static  sf::Vector2i globalMousePostion;
		bool isKeyPressed(enum sf::Keyboard::Key theKey);
	//Calling this variable gets the current postion of the mouse.
 
};
	