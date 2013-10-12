#include <iostream>
#include "gtest/gtest.h"

TEST(coretest, validtest){
	EXPECT_EQ(15, 15);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}