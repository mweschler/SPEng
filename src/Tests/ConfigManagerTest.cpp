#include <iostream>
#include "gtest/gtest.h"
#include "ConfigurationManager.h"
#include "VariableContainer.h"

	ConfigurationManager configurationManager;

TEST(ConfigSuite, storingAndRetrievingIntVariableTest){
	configurationManager.setVariable("Variable1",4);
	int result = configurationManager.getVariable<int>("Variable1");
	EXPECT_EQ(result,4);
}

TEST(ConfigSuite, storingAndRetrievingDoubleVariableTest){
	configurationManager.setVariable("Variable2",4.0);
	double result = configurationManager.getVariable<double>("Variable2");
	EXPECT_EQ(result,4.0);
}

TEST(ConfigSuite, storingAndRetrievingFloatVariableTest){
	configurationManager.setVariable("Variable3",4.0f);
	float result = configurationManager.getVariable<float>("Variable3");
	EXPECT_EQ(result,4.0f);
}

TEST(ConfigSuite, storingAndRetrievingStringVariableTest){
	std::string temp = "4.0";
	configurationManager.setVariable("Variable4",temp);
	std::string result = configurationManager.getVariable<std::string>("Variable4");
	EXPECT_EQ(result,"4.0");
}

TEST(ConfigSuite, storingAndRetrievingCharVariableTest){
	configurationManager.setVariable("Variable5",'4');
	char result = configurationManager.getVariable<char>("Variable5");
	EXPECT_EQ(result,'4');
}
