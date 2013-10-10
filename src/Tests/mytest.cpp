#include <iostream>
#include "gtest/gtest.h"
#include "core.h"

TEST(coretest, validtest){
	int num = dostuff();
	EXPECT_EQ(num, 15);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}