#include "gtest\gtest.h"
#include <fstream>
#include "gui.h"
#include "RenderManager.h"
#include "window.h"
#include "Shader.h"

namespace{
	void writeShaderFiles();

	class ShaderTests: public ::testing::Test{
protected:
	Window *wnd;

	ShaderTests(){
		writeShaderFiles();
	}
	virtual void SetUp(){
		GUI::initialize();
		RenderManager::initialize();
		wnd = GUI::createWindow(800, 600, false);
	}

	virtual void TearDown(){
		wnd->close();
		delete wnd;
		RenderManager::shutdown();
		GUI::shutdown();
	}
};
	std::string fragData = "#version 400\nvoid main(){\ngl_FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n}";
	std::string vertData = "#version 400\nattribute vec4 vertex;\nvoid main(){\ngl_Position = vertex;\n}";


	static void writeShaderFiles()
	{
		std::ofstream file;
		file.open("vertTestShader.vert", std::ios::out);
		file.write(vertData.c_str(),vertData.length());
		file.close();

		file.open("fragTestShader.frag", std::ios::out);
		file.write(fragData.c_str(), fragData.length());
		file.close();
	}

TEST_F(ShaderTests, loadShaderValid){
	Shader vertShader;
	Shader fragShader;
	
	ASSERT_FALSE(vertShader.isCompiled());
	ASSERT_FALSE(vertShader.isLoaded());

	ASSERT_TRUE(vertShader.load("vertTestShader.vert"));
	ASSERT_TRUE(vertShader.isLoaded());

	vertShader.setType(GL_VERTEX_SHADER);
	ASSERT_EQ(GL_VERTEX_SHADER, vertShader.getType());

	ASSERT_TRUE(vertShader.compile());
	ASSERT_TRUE(vertShader.isCompiled());

	ASSERT_NE(vertShader.getID(), 0);

	ASSERT_FALSE(fragShader.isCompiled());
	ASSERT_FALSE(fragShader.isLoaded());

	ASSERT_TRUE(fragShader.load("fragTestShader.frag"));
	ASSERT_TRUE(fragShader.isLoaded());

	fragShader.setType(GL_FRAGMENT_SHADER);
	ASSERT_EQ(GL_FRAGMENT_SHADER, fragShader.getType());

	ASSERT_TRUE(fragShader.compile());
	ASSERT_TRUE(fragShader.isCompiled());

	ASSERT_NE(fragShader.getID(), 0);

	ASSERT_TRUE(vertShader.release());
	ASSERT_FALSE(vertShader.isCompiled());
	ASSERT_TRUE(vertShader.isLoaded());
	ASSERT_EQ(0, vertShader.getID());

	ASSERT_TRUE(fragShader.release());
	ASSERT_FALSE(fragShader.isCompiled());
	ASSERT_TRUE(fragShader.isLoaded());
	ASSERT_EQ(0, fragShader.getID());
}

TEST_F(ShaderTests, invalidUsage){
	Shader shader;
	ASSERT_FALSE(shader.isCompiled());
	ASSERT_FALSE(shader.isLoaded());

	ASSERT_FALSE(shader.compile());
	ASSERT_FALSE(shader.isCompiled());
	ASSERT_FALSE(shader.isLoaded());

	ASSERT_EQ(shader.getID(), 0);
	ASSERT_EQ(shader.getType(), 0);

	ASSERT_TRUE(shader.load("vertTestShader.vert"));
	ASSERT_EQ(shader.getID(), 0);
	ASSERT_EQ(shader.getType(), 0);

	ASSERT_FALSE(shader.isCompiled());
	ASSERT_TRUE(shader.isLoaded());

	ASSERT_FALSE(shader.compile());
	ASSERT_FALSE(shader.isCompiled());
	ASSERT_TRUE(shader.isLoaded());
	ASSERT_EQ(shader.getID(), 0);
	ASSERT_EQ(shader.getType(), 0);

	ASSERT_FALSE(shader.release());
	ASSERT_FALSE(shader.isCompiled());
	ASSERT_TRUE(shader.isLoaded());

	ASSERT_EQ(shader.getID(), 0);
	ASSERT_EQ(shader.getType(), 0);
}

}