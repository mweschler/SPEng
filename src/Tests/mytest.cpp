#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>  

<<<<<<< HEAD

TEST(coretest, validtest){
	EXPECT_EQ(15, 15);
}



int main(int argc, char **argv){
=======

int main(int argc, char **argv)
{
>>>>>>> 07274bbcacb2f33c1b497b2868dbcb7bc18b2870
	::testing::InitGoogleTest(&argc, argv);
	int rv = RUN_ALL_TESTS();
	std::getchar();
	return rv;

}