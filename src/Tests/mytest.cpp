#include <iostream>
#include "gtest/gtest.h"
#include "core.h"
#include "Logger.h"

TEST(coretest, validtest){
	int num = dostuff();
	EXPECT_EQ(num, 15);
}


TEST(logger, test_one){
	Logger logger;
	int k = logger.createLog();
	EXPECT_EQ(k, 0);
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();

}