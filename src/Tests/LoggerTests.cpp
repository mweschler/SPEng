#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>  




TEST(logger, test_one_testsIfDataLogIsDetectedOnceItIsCreated)
{
	Logger* logger = Logger::Instance();
    logger->initialize();
	bool b = logger -> getDataLogExists();
	logger->deleteLog();
	EXPECT_EQ(b, true);
}

TEST(logger, test_two_TryingToWriteToTheLogButItDoesNotExist)
{
	Logger* logger = Logger::Instance();
	int k = logger->writeToLog("Hello this is a test for the log.");
	logger->shutdown();
	logger->deleteLog();
	EXPECT_EQ(k, 0);
}


TEST(logger, test_three_TryingToWriteToTheLogAndItDoesExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	int k = logger->writeToLog("This is a test for the log.");
	logger->shutdown();
	logger->deleteLog();
	EXPECT_EQ(k, 1);
}


TEST(logger, test_four_TryingToDeleteALogButItDoesNotExist)
{
	Logger* logger = Logger::Instance();
	int k = logger->deleteLog();
	EXPECT_EQ(k, 0);
}

TEST(logger, test_five_TryingToDeleteALogAndItDoesExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog("This is a test for the log.");
	logger->shutdown();
	int k = logger->deleteLog();
	
	EXPECT_EQ(k, 1);
}



TEST(logger, DISABLED_personal_test_if_it_writes_corrrectly)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog("This is a test for the log.");
	logger->writeToLog("This is another test for the log.");
	logger->shutdown();
	EXPECT_EQ(1, 1);
}




