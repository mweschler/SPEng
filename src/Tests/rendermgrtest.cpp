#include "gtest\gtest.h"
#include "RenderManager.h"
#include "gui.h"
#include "window.h"
#include "GLBuffer.h"

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

	class GLBufferTests: public::testing::Test
	{
	protected:
		Window *wnd;
		virtual void SetUp(){
			GUI::initialize();
			RenderManager::initialize();
			wnd = GUI::createWindow(800, 600, false);
		}
		virtual void TearDown(){
			wnd->close();
			delete wnd;
			wnd = NULL;
			RenderManager::shutdown();
			GUI::shutdown();
		}
	};

	TEST_F(GLBufferTests, creationBindReleaseValid){
		ASSERT_TRUE(GUI::isInitialized());
		ASSERT_TRUE(RenderManager::isInitialized());
		ASSERT_TRUE(wnd != NULL);
		wnd->makeContextCurrent();
		GLBuffer buffer(GL_ARRAY_BUFFER);
		ASSERT_EQ(GL_ARRAY_BUFFER, buffer.getType());
		ASSERT_TRUE(buffer.create());
		ASSERT_TRUE(buffer.bind());
		ASSERT_TRUE(buffer.release());
	}

	TEST_F(GLBufferTests, DISABLED_creationBindReleaseInvalid){
		ASSERT_TRUE(GUI::isInitialized());
		ASSERT_TRUE(RenderManager::isInitialized());
		ASSERT_TRUE(wnd != NULL);
		wnd->makeContextCurrent();
		GLBuffer badBuffer(GL_TRUE);
		ASSERT_EQ(GL_TRUE, badBuffer.getType());
		ASSERT_TRUE(badBuffer.create());
		ASSERT_FALSE(badBuffer.bind());
		ASSERT_TRUE(badBuffer.release());

		GLBuffer buffer(GL_ARRAY_BUFFER);
		ASSERT_FALSE(buffer.bind());
		ASSERT_FALSE(buffer.release());
		ASSERT_TRUE(buffer.create());
		ASSERT_TRUE(buffer.bind());
		//NEED MORE
	}
}