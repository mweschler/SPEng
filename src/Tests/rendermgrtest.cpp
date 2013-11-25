#include "gtest\gtest.h"
#include "RenderManager.h"
#include "gui.h"
#include "window.h"
#include "GLBuffer.h"
#include "Model.h"
#include "Logger.h"
#include "GLHelper.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Camera.h"

#define _USE_MATH_DEFINES

#include <math.h>


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

		Logger &logger = *Logger::Instance();
		ASSERT_TRUE(logger.initialize());

		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());

		
	}

	TEST(RenderTests, renderInitInvalid){
		Logger &logger = *Logger::Instance();
		ASSERT_TRUE(logger.initialize());

		ASSERT_FALSE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		ASSERT_FALSE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());

		logger.shutdown();
	}

	TEST(RenderTests, renderUpdate){
		Logger &logger = *Logger::Instance();
		ASSERT_TRUE(logger.initialize());

		ASSERT_FALSE(RenderManager::isInitialized());
		ASSERT_TRUE(RenderManager::initialize());
		ASSERT_TRUE(RenderManager::isInitialized());
		RenderManager::update();
		RenderManager::shutdown();
		ASSERT_FALSE(RenderManager::isInitialized());

		logger.shutdown();
	}

	class GLBufferTests: public::testing::Test
	{
	protected:
		GLBufferTests(){
			GLHelper::flushGLErrors();
		}
		Window *wnd;
		virtual void SetUp(){
			Logger &logger = *Logger::Instance();
			logger.initialize();

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
			Logger &logger = *Logger::Instance();
			logger.shutdown();
		}
	};

	TEST_F(GLBufferTests, creationBindReleaseValid){
		GLHelper::flushGLErrors();
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

	TEST_F(GLBufferTests, creationBindReleaseInvalid){
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
		ASSERT_FALSE(buffer.create());
		ASSERT_TRUE(buffer.bind());
		ASSERT_TRUE(buffer.release());
		ASSERT_FALSE(buffer.bind());
		ASSERT_FALSE(buffer.release());
	}

	class ModelTests : public ::testing::Test{
	protected:
		Window *wnd;
		virtual void SetUp(){
			Logger *logger = Logger::Instance();
			logger->initialize();
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
			Logger *logger = Logger::Instance();
			logger->shutdown();
		}
	};

	const GLfloat verts[] = {
		0.25f, 0.25f, 0.0f, 1.0f,
		0.50f, 0.50f, 0.0f, 1.0f,
		0.25f, 0.50f, 0.0f, 1.0f
	};

	const GLfloat normals[] = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f
	};

	const GLushort indicies[] = {
		0, 1, 2
	};

	TEST_F(ModelTests, creationVertValid){
		Model model;
		ASSERT_FALSE(model.isLoaded());
		std::vector<GLfloat> vertData(std::begin(verts), std::end(verts));
		ASSERT_TRUE(model.load(vertData));
		ASSERT_TRUE(model.isLoaded());
		ASSERT_TRUE(model.hasVerts());
		ASSERT_FALSE(model.hasNormals());
		ASSERT_FALSE(model.hasIndex());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		ASSERT_TRUE(model.bind(Model::VERTEX));
		ASSERT_TRUE(model.release());
		ASSERT_FALSE(model.isLoaded());
		ASSERT_FALSE(model.hasVerts());
	}

	TEST_F(ModelTests, creationVertInvalid){
		Model model;
		ASSERT_FALSE(model.isLoaded());
		ASSERT_FALSE(model.hasVerts());
		ASSERT_FALSE(model.hasNormals());
		ASSERT_FALSE(model.hasIndex());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		ASSERT_FALSE(model.bind(Model::VERTEX));
		ASSERT_FALSE(model.bind(Model::INDEX));
		ASSERT_FALSE(model.bind(Model::NORMAL));
		ASSERT_FALSE(model.release());
		ASSERT_FALSE(model.isLoaded());
		std::vector<GLfloat> vertData(std::begin(verts), std::end(verts));
		ASSERT_TRUE(model.load(vertData));
		ASSERT_TRUE(model.isLoaded());
		ASSERT_TRUE(model.hasVerts());
		ASSERT_FALSE(model.load(vertData));
		ASSERT_TRUE(model.isLoaded());
		ASSERT_TRUE(model.hasVerts());
		ASSERT_TRUE(model.bind(Model::VERTEX));
		ASSERT_TRUE(model.release());
		ASSERT_FALSE(model.isLoaded());
		ASSERT_FALSE(model.hasVerts());
		ASSERT_FALSE(model.bind(Model::VERTEX));
		ASSERT_FALSE(model.release());
	}

	TEST_F(ModelTests, creationVertIndexValid){
		Model model;
		ASSERT_FALSE(model.isLoaded());
		std::vector<GLfloat> vertData(std::begin(verts), std::end(verts));
		std::vector<GLushort> indexData(std::begin(indicies), std::end(indicies));
		ASSERT_TRUE(model.load(vertData, indexData));
		ASSERT_TRUE(model.isLoaded());
		ASSERT_TRUE(model.hasVerts());
		ASSERT_FALSE(model.hasNormals());
		ASSERT_TRUE(model.hasIndex());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		ASSERT_TRUE(model.bind(Model::VERTEX));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		ASSERT_TRUE(model.bind(Model::INDEX));
		ASSERT_TRUE(model.release());
		ASSERT_FALSE(model.isLoaded());
		ASSERT_FALSE(model.hasVerts());
		ASSERT_FALSE(model.hasIndex());
	}

	TEST_F(ModelTests, creationVertNormIndexValid){
		Model model;
		ASSERT_FALSE(model.isLoaded());
		std::vector<GLfloat> vertData(std::begin(verts), std::end(verts));
		std::vector<GLushort> indexData(std::begin(indicies), std::end(indicies));
		std::vector<GLfloat> normalData(std::begin(normals), std::end(normals));
		ASSERT_TRUE(model.load(vertData, normalData, indexData));
		ASSERT_TRUE(model.isLoaded());
		ASSERT_TRUE(model.hasVerts());
		ASSERT_TRUE(model.hasNormals());
		ASSERT_TRUE(model.hasIndex());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		ASSERT_TRUE(model.bind(Model::VERTEX));
		ASSERT_TRUE(model.bind(Model::NORMAL));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		ASSERT_TRUE(model.bind(Model::INDEX));
		ASSERT_TRUE(model.release());
		ASSERT_FALSE(model.isLoaded());
		ASSERT_FALSE(model.hasVerts());
		ASSERT_FALSE(model.hasNormals());
		ASSERT_FALSE(model.hasIndex());
	}

	void writeShaderFiles();

	std::string fragData = "\nuniform vec3 lightDir;\nuniform vec4 lightColor;\nuniform vec4 ambient;\nuniform vec3 diffuse;\nvarying vec3 vertexNormal;\nvoid main(){\nfloat cosAngIncidence = dot(normalize(vertexNormal), lightDir);\ncosAngIncidence = clamp(cosAngIncidence, 0, 1);\ngl_FragColor = ((vec4(diffuse, 1.0f) * lightColor * cosAngIncidence) + (vec4(diffuse, 1.0f) * ambient));\n}";
	std::string fragData4 = "\nuniform vec3 lightDir;\nuniform vec4 lightColor;\nuniform vec4 ambient;\nuniform vec3 diffuse;\in vec3 vertexNormal;\nout vec4 color;\nvoid main(){\nfloat cosAngIncidence = dot(normalize(vertexNormal), lightDir);\ncosAngIncidence = clamp(cosAngIncidence, 0, 1);\ncolor = (vec4(diffuse, 1.0f) * lightColor * cosAngIncidence) + (vec4(diffuse, 1.0f) * ambient);\n}";
	std::string vertData = "\nuniform mat4 mvp;\nattribute vec4 vertex;\nvarying vec3 vertexNormal;\nattribute vec3 normal;\nvoid main(){\nvertexNormal = normal ;\ngl_Position = mvp * vertex;\n}";
	std::string vertData4 = "\nuniform mat4 mvp;\nin vec4 vertex;\nout vec4 position;\out vec3 vertexNormal;\nin vec3 normal;\nvoid main(){\nvertexNormal = normal ;\nposition = mvp * vertex;\n}";

	class Render3DTests: public ::testing::Test{
	protected:
		Render3DTests(){
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
			
			writeShaderFiles();}
		~Render3DTests(){}

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


	TEST_F(Render3DTests, DISABLED_visualTest){

		const float triangle[] ={
				-0.75f, 0.75f, 0.0f, 1.0f,
				-0.75f, -0.75f, 0.0f, 1.0f,
				0.75f, -0.75f, 0.0f, 1.0f,
		};

		const GLushort indicies[] = {0, 1, 2};

		Model triangleModel;
		std::vector<float> data( std::begin(triangle), std::end(triangle));
		std::vector<GLushort> index(std::begin(indicies), std::end(indicies));
		ASSERT_TRUE(triangleModel.load(data, index));
		triangleModel.setVertCount(3);
		triangleModel.setIndexCount(3);

		Shader frag;
		Shader vert;
		ShaderProgram program;
		Material material;
		Camera camera;

		ASSERT_TRUE(vert.load("vertTestShader.vert"));
		ASSERT_TRUE(frag.load("fragTestShader.frag"));

		vert.setType(GL_VERTEX_SHADER);
		frag.setType(GL_FRAGMENT_SHADER);

		ASSERT_TRUE(vert.compile());
		ASSERT_TRUE(frag.compile());

		ASSERT_TRUE(program.link(vert, frag));
		program.setVertAttrib("vertex");
		program.setDiffuseAttrib("diffuse");
		//program.setMVPAttrib("mvp");

		ASSERT_TRUE(material.setShader(&program));
		material.setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
		
		float camDeg = 0;
		camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	
		RenderManager::set3DMode(45);
		wnd->show();
		while(!wnd->shouldQuit()){
			wnd->pollEvents();
			RenderManager::update();

			float camX = sin(camDeg * M_PI / 180) * 1;
			float camZ = cos(camDeg * M_PI / 180) * 1;
			camera.setPosition(glm::vec3(camX, 0.0f, camZ));
			//std::cout<<"Cam deg  "<<camDeg<<" pos "<<camX<<" 0.0f "<<camZ<<std::endl;
			RenderManager::drawModel(triangleModel, material, camera);
			wnd->swapBuffers();

			camDeg = camDeg + 0.5;
			if(camDeg >= 360)
				camDeg = 0;
		}
		std::cout<<"end of loop\n";

		triangleModel.release();

		program.release();

		frag.release();

		vert.release();

	}

	TEST_F(Render3DTests, DISABLED_modelVisualTest){

		const GLushort indicies[] = {0, 1, 2};

		Model deco;

		ASSERT_TRUE(deco.load("decocube.obj"));
		
		Shader frag;
		Shader vert;
		ShaderProgram program;
		Material material;
		Camera camera;

		ASSERT_TRUE(vert.load("vertTestShader.vert"));
		ASSERT_TRUE(frag.load("fragTestShader.frag"));

		vert.setType(GL_VERTEX_SHADER);
		frag.setType(GL_FRAGMENT_SHADER);

		ASSERT_TRUE(vert.compile());
		ASSERT_TRUE(frag.compile());

		ASSERT_TRUE(program.link(vert, frag));
		program.setVertAttrib("vertex");
		program.setDiffuseAttrib("diffuse");
		program.setMVPAttrib("mvp");
		program.setAmbientAttrib("ambient");
		program.setLightAttribs("lightDir", "lightColor");
		program.setNormAttrib("normal");
		
		//RenderManager::setAmbient(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ASSERT_TRUE(material.setShader(&program));
		material.setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
		
		float camDeg = 0;
		camera.setTarget(glm::vec3(0.0f, 1.0f, 0.0f));
	
		RenderManager::set3DMode(45);
		wnd->show();
		while(!wnd->shouldQuit()){
			wnd->pollEvents();
			RenderManager::update();

			float camX = sin(camDeg * M_PI / 180) * 5;
			float camZ = cos(camDeg * M_PI / 180) * 5;
			camera.setPosition(glm::vec3(camX, 1.0f, camZ));
			//std::cout<<"Cam deg  "<<camDeg<<" pos "<<camX<<" 0.0f "<<camZ<<std::endl;
			RenderManager::drawModel(deco, material, camera);
			wnd->swapBuffers();

			camDeg = camDeg + 0.5;
			if(camDeg >= 360)
				camDeg = 0;
		}
		std::cout<<"end of loop\n";

		deco.release();

		program.release();

		frag.release();

		vert.release();

	}
}