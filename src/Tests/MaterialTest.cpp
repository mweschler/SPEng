#include <gtest\gtest.h>
#include "gui.h"
#include "window.h"
#include "material.h"
#include "Logger.h"
#include "RenderManager.h"
#include "Shader.h"
#include "Model.h"

namespace{
	void writeShaderFiles();

	std::string fragData = "\nvoid main(){\ngl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n}";
	std::string fragData4 = "\nout vec4 color;\nvoid main(){\ncolor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n}";
	std::string vertData = "\nattribute vec4 vertex;\nvoid main(){\ngl_Position = vertex;\n}";
	std::string vertData4 = "\nin vec4 vertex;\nvoid main(){\ngl_Position = vertex;\n}";

	class MaterialTest:public ::testing::Test{
	protected:
		MaterialTest(){
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

		Window *wnd;

		void SetUp(){
			GUI::initialize();
			RenderManager::initialize();
			wnd = GUI::createWindow(800, 600, false);
		}

		void TearDown(){
			wnd->close();
			delete wnd;
			wnd = NULL;
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

	TEST_F(MaterialTest, matCreationTest)
	{
		Shader vert;
		Shader frag;

		ASSERT_TRUE(vert.load("vertTestShader.vert"));
		vert.setType(GL_VERTEX_SHADER);
		ASSERT_TRUE(vert.compile());

		ASSERT_TRUE(frag.load("fragTestShader.frag"));
		frag.setType(GL_FRAGMENT_SHADER);
		ASSERT_TRUE(frag.compile());

		ShaderProgram program;
		ASSERT_TRUE(program.link(vert, frag));
		
		Material mat;
		ASSERT_TRUE(mat.setShader(&program));
		glm::vec3 color;
		color.r = 1.0f;
		color.g = 2.0f;
		color.b = 3.0f;

		mat.setDiffuseColor(color);
		glm::vec3 rv = mat.getDiffuseColor();

		ASSERT_EQ(color, rv);

		ASSERT_TRUE(program.release());
		ASSERT_TRUE(frag.release());
		ASSERT_TRUE(vert.release());
	}

	TEST_F(MaterialTest, DISABLED_visualTest){
		const float triangle[] ={
				0.75f, 0.75f, 0.0f, 1.0f,
				0.75f, -0.75f, 0.0f, 1.0f,
				-0.75f, -0.75f, 0.0f, 1.0f,
		};

		const GLushort indicies[] = {0, 1, 2};

		Model triangleModel;
		std::vector<float> data( std::begin(triangle), std::end(triangle));
		std::vector<GLushort> index(std::begin(indicies), std::end(indicies));
		ASSERT_TRUE(triangleModel.load(data, index));
		triangleModel.setVertCount(3);
		triangleModel.setIndexCount(3);

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

		Material mat;
		ASSERT_TRUE(mat.setShader(&program));

		mat.setVertAtrib("vertex");


		wnd->show();
		while(!this->wnd->shouldQuit()){
			wnd->pollEvents();

			RenderManager::update();
			RenderManager::drawModel(triangleModel, mat);

			wnd->swapBuffers();		
		}
	}
}