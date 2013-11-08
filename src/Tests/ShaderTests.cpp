#include "gtest\gtest.h"
#include <fstream>
#include "gui.h"
#include "RenderManager.h"
#include "window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Logger.h"

namespace{
	void writeShaderFiles();

	std::string fragData = "\nvoid main(){\ngl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n}";
	std::string fragData4 = "\nout vec4 color;\nvoid main(){\ncolor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n}";
	std::string vertData = "\nattribute vec4 vertex;\nvoid main(){\ngl_Position = vertex;\n}";
	std::string vertData4 = "\nin vec4 vertex;\nvoid main(){\ngl_Position = vertex;\n}";

	class ShaderTests: public ::testing::Test{
protected:
	Window *wnd;

	ShaderTests(){
		Logger &logger = *Logger::Instance();
		logger.initialize();
		GUI::initialize();
		Window *tmp = GUI::createWindow(800, 600, false);
		std::string version = "#version ";
		switch(tmp->getMajorVersion())
		{
		case 4: version = version +"400"; 
			vertData = vertData4; 
			fragData = fragData4;
			break;
		case 3: version = version + "300"; break;
		case 2: version = version + "120"; break;
		default: version = version + "120";break;
		}

		fragData = version + fragData;
		vertData = version + vertData;
		tmp->close();
		delete tmp;
		GUI::shutdown();
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

TEST_F(ShaderTests, programValid){
	Shader vertShader;
	Shader fragShader;
	
	ASSERT_TRUE(vertShader.load("vertTestShader.vert"));
	ASSERT_TRUE(fragShader.load("fragTestShader.frag"));

	vertShader.setType(GL_VERTEX_SHADER);
	fragShader.setType(GL_FRAGMENT_SHADER);

	ASSERT_TRUE(vertShader.compile());
	ASSERT_TRUE(fragShader.compile());

	ShaderProgram program;

	ASSERT_FALSE(program.isLinked());
	
	ASSERT_TRUE(program.link(vertShader, fragShader));
	ASSERT_TRUE(program.isLinked());

	ASSERT_TRUE(program.use());

	ASSERT_TRUE(program.release());
	ASSERT_FALSE(program.isLinked());
}

//simple visual test
TEST_F(ShaderTests, DISABLED_visualTest){

	const float triangle[] ={
				0.75f, 0.75f, 0.0f, 1.0f,
				0.75f, -0.75f, 0.0f, 1.0f,
				-0.75f, -0.75f, 0.0f, 1.0f,
	};
	GLuint triangleBuff;

	glGenBuffers(1, &triangleBuff);
	glBindBuffer(GL_ARRAY_BUFFER, triangleBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Shader vert;
	Shader frag;
	ShaderProgram program;

	ASSERT_TRUE(vert.load("vertTestShader.vert"));
	ASSERT_TRUE(frag.load("fragTestShader.frag"));

	vert.setType(GL_VERTEX_SHADER);
	frag.setType(GL_FRAGMENT_SHADER);

	ASSERT_TRUE(vert.compile());
	ASSERT_TRUE(frag.compile());

	ASSERT_TRUE(program.link(vert, frag));
	

	wnd->show();
	while(!this->wnd->shouldQuit()){
		wnd->pollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		program.use();
		glBindBuffer(GL_ARRAY_BUFFER, triangleBuff);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		wnd->swapBuffers();		
	}
}

}
