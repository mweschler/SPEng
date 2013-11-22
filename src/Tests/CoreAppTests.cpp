#include "coregameapp.h"
#include "gtest\gtest.h"
#include "window.h"

namespace {
	class CoreAppTests : public ::testing::Test 
	{
	public: 
		CoreAppTests() {}
		~CoreAppTests() {}
	protected:
		void SetUp(){}
		void TearDown(){}		
	};

	class UserApp : public CoreGameApp{
	protected:
		virtual bool initialize(){
			once = false;
			return true;}
		virtual void update(){
			if(!once){
				Window *wnd = this->getWindow();
				wnd->show();
				once = true;
			}
		}
		virtual void render(){}
		virtual void shutdown(){}
	private:
		bool once;
	};

	TEST_F(CoreAppTests, DISABLED_validUserAppRun){
		UserApp app;
		char *args[1];
		args[0] = "";

		app.run(0, args);
	}
}