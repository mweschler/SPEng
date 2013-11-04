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

TEST(assetTests, test_two_testDuplicateMethod_Yes_Duplicate)
{
	//Asset asset = new Asset();
	AssetManager* manager = AssetManager::Instance();
	manager -> loadAsset<Asset>("C:\\Users\jnoda009\\Pictures\\tree");
	manager -> loadAsset<Asset>("C:\\Users\jnoda009\\Pictures\\dragon");
	bool b = manager -> checkForDuplicate("C:\\Users\jnoda009\\Pictures\\dragon");
	EXPECT_EQ(b, true);
}

TEST(assetTests, test_three_testIfReferenceCountIncreases)
{
	AssetManager* manager = AssetManager::Instance();
	manager -> loadAsset<Asset>("C:\\Users\jnoda009\\Pictures\\tree");
	manager -> loadAsset<Asset>("C:\\Users\jnoda009\\Pictures\\tree");
	int b = manager -> getRefCount("C:\\Users\jnoda009\\Pictures\\tree");
	EXPECT_EQ(b, 3);
}
