#include <iostream>
#include "gtest/gtest.h"
#include "ConfigurationManager.h"
#include "VariableContainer.h"

ConfigurationManager* configurationManager = ConfigurationManager::Instance();

TEST(ConfigSuite, storingAndRetrievingIntVariableTest){
	configurationManager->setVariable("Variable1",4);
	int result = configurationManager->getVariable<int>("Variable1");
	EXPECT_EQ(4,result);
}

TEST(ConfigSuite, storingAndRetrievingDoubleVariableTest){
	configurationManager->setVariable("Variable2",4.0);
	double result = configurationManager->getVariable<double>("Variable2");
	EXPECT_EQ(4.0,result);
}

TEST(ConfigSuite, storingAndRetrievingFloatVariableTest){
	configurationManager->setVariable("Variable3",4.0f);
	float result = configurationManager->getVariable<float>("Variable3");
	EXPECT_EQ(4.0f,result);
}

TEST(ConfigSuite, storingAndRetrievingStringVariableTest){
	std::string temp = "4.0";
	configurationManager->setVariable("Variable4",temp);
	std::string result = configurationManager->getVariable<std::string>("Variable4");
	EXPECT_EQ("4.0",result);
}

TEST(ConfigSuite, storingAndRetrievingCharVariableTest){
	configurationManager->setVariable("Variable5",'4');
	char result = configurationManager->getVariable<char>("Variable5");
	EXPECT_EQ('4',result);
}

TEST(ConfigSuite, testingSingletonDesignPattern){
	ConfigurationManager* configurationManager2 = ConfigurationManager::Instance();
	int intResult = configurationManager2->getVariable<int>("Variable1");
	double doubleResult = configurationManager2->getVariable<double>("Variable2");
	float floatResult = configurationManager2->getVariable<float>("Variable3");
	std::string stringResult = configurationManager2->getVariable<std::string>("Variable4");
	char charResult = configurationManager2->getVariable<char>("Variable5");
	EXPECT_EQ(4,intResult);
	EXPECT_EQ(4.0,doubleResult);
	EXPECT_EQ(4.0f,floatResult);
	EXPECT_EQ("4.0",stringResult);
	EXPECT_EQ('4',charResult);
}
