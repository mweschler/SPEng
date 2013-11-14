#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>  

int main(int argc, char **argv)
{
	::testing::GTEST_FLAG(filter) = "*AudioSuite*";
	::testing::InitGoogleTest(&argc, argv);
	int rv = RUN_ALL_TESTS();
	std::getchar();
	return rv;
}