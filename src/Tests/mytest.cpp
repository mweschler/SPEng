#include "gtest/gtest.h"
#include "core.h"

TEST(coretest, validtest){
	int num = dostuff();
	EXPECT_EQ(num, 15);
}
