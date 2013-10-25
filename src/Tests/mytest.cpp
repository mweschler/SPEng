#include <iostream>
#include "gtest/gtest.h"
<<<<<<< HEAD
#include "core.h"
#include "Logger.h"
=======
>>>>>>> 1eff059eda3bc724ae997baf1d6fa4d90be782dc

TEST(coretest, validtest){
	EXPECT_EQ(15, 15);
}


TEST(logger, test_one){
	Logger logger;
	int k = logger.createLog();
	EXPECT_EQ(k, 0);
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
<<<<<<< HEAD
	
	return RUN_ALL_TESTS();

=======
	int rv = RUN_ALL_TESTS();
	std::getchar();
	return rv;
>>>>>>> 1eff059eda3bc724ae997baf1d6fa4d90be782dc
}