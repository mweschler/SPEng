#include "coregameapp.h"
#include "gtest\gtest.h"
#include "window.h"

namespace {

	static int output = -1;
	static int renders = -1;
	static bool ishutdown = false;
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
			output = 0;
			renders = 0;
			return true;}
		virtual void update(){
			if(output >= 10)
				this->quit();
			else
				output++;
		}
		virtual void render(){
			renders++;
		}
		virtual void shutdown(){
			ishutdown = true;
		}
	private:
		bool once;
	};

	class BrokenInit : public CoreGameApp{
	protected:
		virtual bool initialize(){
			return false;
		}

		virtual void update(){

		}

		virtual void render(){
		}

		virtual void shutdown(){

		}
	};

	TEST_F(CoreAppTests, validUserAppRun){
		UserApp app;
		char *args[1];
		args[0] = "";

		ASSERT_EQ(0, app.run(0, args));
		ASSERT_EQ(output, 10);
		ASSERT_EQ(renders, 11);
		ASSERT_TRUE(ishutdown);
	}

	TEST_F(CoreAppTests, badInit){
		BrokenInit binit;
		char *args[1];
		args[0] = "";

		ASSERT_EQ(-1, binit.run(0, args));
	}
}