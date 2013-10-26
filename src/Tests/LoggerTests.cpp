#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>  


/*
TEST(logger, test_one_TryingToCreateLogWithoutItExisting)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	int k = logger->createLog();
	logger->deleteLog();
	EXPECT_EQ(k, 1);
}



TEST(logger, test_two_TryingToCreateLogbutLogAlreadyExists)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	int k = logger->createLog();
	int n = logger->createLog();
	logger->deleteLog();
	EXPECT_EQ(n, 0);
}



TEST(logger, test_three_TryingToWriteToTheLogButItDoesNotExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	int k = logger->writeToLog("Hello this is a test for the log.");
	EXPECT_EQ(k, 0);
}


TEST(logger, test_four_TryingToWriteToTheLogAndItDoesExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->createLog();
	int k = logger->writeToLog("This is a test for the log.");
	logger->deleteLog();
	EXPECT_EQ(k, 1);
}


TEST(logger, test_five_TryingToDeleteALogButItDoesNotExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	int k = logger->deleteLog();
	EXPECT_EQ(k, 0);
}


TEST(logger, test_six_TryingToDeleteALogAndItDoesExist)
{
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->createLog();
	logger->writeToLog("This is a test for the log.");
	int k = logger->deleteLog();
	EXPECT_EQ(k, 1);
}



*/