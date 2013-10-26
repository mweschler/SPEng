#include "gtest/gtest.h"
#include "gui.h"
#include "window.h"

namespace {
class WindowTests : public ::testing::Test{
protected:
	WindowTests(){ 
		
	}

	~WindowTests() {
		
	}
	virtual void SetUp(){
		GUI::initialize();
	}

	virtual void TearDown(){
		GUI::shutdown();
	}
	
};


TEST(GUITests, initTestValid){
	ASSERT_TRUE(GUI::initialize());
	ASSERT_TRUE(GUI::isInitialized());
	GUI::shutdown();
	ASSERT_FALSE(GUI::isInitialized());
}

TEST(GUITests, initTestInvalid){
	ASSERT_FALSE(GUI::isInitialized());
	ASSERT_TRUE(GUI::initialize());
	ASSERT_FALSE(GUI::initialize());
	GUI::shutdown();
	ASSERT_FALSE(GUI::isInitialized());
}

TEST(GUITests, windowCreationValid){
	ASSERT_TRUE(GUI::initialize());
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->close();
	delete wnd;
	GUI::shutdown();
}

TEST(GUITests, windowCreationInvalidRes){
	ASSERT_TRUE(GUI::initialize());
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(0, 0, false);
	ASSERT_TRUE(wnd == NULL);
	GUI::shutdown();
}

TEST_F(WindowTests, windowShow){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800,600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->show();
	/*
	while(!wnd->shouldQuit()){
		wnd->pollEvents();
	}*/
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSetColorBitValid){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->setColorBits(32);
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSetDepthBits){
	ASSERT_TRUE(GUI::isInitialized());
	
	Window * wnd =  GUI::createWindow(800, 600, false);
	ASSERT_TRUE( wnd != NULL);
	wnd->setDepthBits(8);
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSetStencilBis){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE( wnd != NULL);
	wnd->setStencilBits(8);
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSetDoubleBuffer){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE( wnd != NULL);
	wnd->setDoubleBuffer(true);
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowCursor){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800,600, false);
	ASSERT_TRUE( wnd != NULL);
	wnd->showCursor(false);
	wnd->showCursor(true);
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowEventPolling){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->pollEvents();
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSetCurent){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->makeContextCurrent();
	wnd->close();
	delete wnd;
}

TEST_F(WindowTests, windowSwapBuffers){
	ASSERT_TRUE(GUI::isInitialized());

	Window *wnd = GUI::createWindow(800, 600, false);
	ASSERT_TRUE(wnd != NULL);
	wnd->swapBuffers();
	wnd->close();
	delete wnd;
}


}