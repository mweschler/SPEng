#include "gtest/gtest.h"
#include "InputHandler.h"

//If this test gives you an error. It means you were pressing up
TEST(userInputTest, test_one)
{
	UserInput input;

	bool test =input.isKeyPressed(sf::Keyboard::Up);
	input.isKeyPressed(sf::Keyboard::Up);
	ASSERT_EQ(false,	test);
}
