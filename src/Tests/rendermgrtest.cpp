#include "gtest\gtest.h"
#include "RenderManager.h"

namespace{
	class RenderTests : public ::testing::Test{
	protected:
		virtual void SetUp(){
			RenderManager::initialize();
		}

		virtual void TearDown(){
			RenderManager::shutdown();
		}
	};

	TEST(RenderTests, renderInitValid){
		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());
	}

	TEST(RenderTests, renderInitInvalid){
		ASSERT_FALSE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		ASSERT_FALSE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());
	}

	TEST(RenderTests, renderUpdate){
		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::update();
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());
	}

}