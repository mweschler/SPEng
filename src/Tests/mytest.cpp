#include <iostream>
#include "gtest/gtest.h"


TEST(coretest, validtest){
	EXPECT_EQ(15, 15);
}



int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	int rv = RUN_ALL_TESTS();
	std::getchar();
	return rv;
}