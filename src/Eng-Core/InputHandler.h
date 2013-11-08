#include <stdio.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
class UserInput
{
	
public:
		bool isMouseKeyPressed(enum sf::Mouse::Button theButton);
		sf::Vector2i getMousePosition();
	 	bool isKeyPressed(enum sf::Keyboard::Key theKey);
	    void setMousePostion(int x, int y);
 
};
	