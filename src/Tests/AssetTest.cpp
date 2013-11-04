#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include "Asset.h"
#include "AssetManager.h"


TEST(assetTests, test_one_testDuplicateMethod_No_Duplicate)
{
	//Asset asset = new Asset();
	AssetManager* manager = AssetManager::Instance();
	Asset* asset = new Asset("C:\\Users\jnoda009\\Pictures\\lemons");
	bool b = manager -> checkForDuplicate(asset->getName());
	EXPECT_EQ(b, false);
}


/*
TEST(assetTests, test_two_testDuplicateMethod_Yes_ThereIsADuplicate)
{
	//Asset asset = new Asset();
	AssetManager* manager = AssetManager::Instance();
	Asset* asset = new Asset("C:\\Users\jnoda009\\Pictures\\lemons");
	Asset a = manager->loadAsset<Asset>("C:\\Users\jnoda009\\Pictures\\lemons");
	bool b = manager -> checkForDuplicate("C:\\Users\jnoda009\\Pictures\\lemons");
	EXPECT_EQ(b, true);
}


*/