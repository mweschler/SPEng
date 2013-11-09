#include "gtest\gtest.h"
#include "RenderManager.h"
#include "gui.h"
#include "window.h"
#include "GLBuffer.h"
#include "Model.h"
#include "Logger.h"

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

}