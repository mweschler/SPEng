#include <iostream>
#include "gtest/gtest.h"
#include "ConfigurationManager.h"
#include "VariableContainer.h"

TEST(ConfigSuite, variableTest){
	ConfigurationManager configurationManager;
	configurationManager.setVariable<int>("firstValue",0);
	EXPECT_EQ(configurationManager.getVariable<int>("firstValue"),0);
}
