#include "engdemo.h"
#include "window.h"
#include "GameWorld.h"
#include "GameObject.h"
#include <memory>
#include "renderList.h"
#include "modelComponent.h"
#include <AssetManager.h>
#include "Shader.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Logger.h"
#include "gui.h"
#include "RenderManager.h"
#include "ScriptComponent.h"
#include "ScriptingManager.h"
#include "InputHandler.h"
#include <glm/ext.hpp>
#include <xtgmath.h>
#include <limits.h>

static bool doOnce = false;

typedef std::numeric_limits< double > dbl;

EngDemoApp::EngDemoApp():
	m_texture(NULL)
{

}

bool EngDemoApp::initialize(){

	return true;
}

ModelComponent *modelComp;
float rotation = 0.0f;
void EngDemoApp::update(){
	Logger &logger = *Logger::Instance();

	if(!doOnce)
	{
		AssetManager &assetManager = *AssetManager::Instance();
		m_model = (Model *)assetManager.loadAsset<Model>("targetobj.obj");
		if(m_model == NULL)
		{
			logger.writeToLog("Could not load model, quitting");
			GUI::showMessageBox("Could not load model. Quitting", "Error");
			this->quit();
			return;
		}

		m_vertShader = (Shader *)assetManager.loadAsset<Shader>("demoVert12.vert");
		if(m_vertShader == NULL){
			logger.writeToLog("Could not load vert shader, quitting");
			GUI::showMessageBox("Could not load vert shader. Quitting", "Error");
			this->quit();
			return;
		}
		m_fragShader = (Shader *)assetManager.loadAsset<Shader>("demoFrag12.frag");
		if(m_fragShader == NULL){
			logger.writeToLog("Could not load frag shader, quitting");
			GUI::showMessageBox("Could not load frag shader. Quitting", "Error");
			this->quit();
			return;
		}

		m_vertShader->setType(GL_VERTEX_SHADER);
		if(!m_vertShader->compile()){
			logger.writeToLog("Could not compile vert shader. Quitting");
			GUI::showMessageBox("Could not compile vert shader. Quitting", "Error");
			this->quit();
			return;
		}

		m_fragShader->setType(GL_FRAGMENT_SHADER);
		if(!m_fragShader->compile()){
			logger.writeToLog("Could not compile frag shader. Quitting");
			GUI::showMessageBox("Could not compile frag shader. Quitting", "Error");
			this->quit();
			return;
		}

		if(!m_program.link(*m_vertShader, *m_fragShader)){
			logger.writeToLog("Could not link shader program. Quitting");
			GUI::showMessageBox("Could not link shader. Quitting", "Error");
			this->quit();
			return;
		}

		m_texture = (Texture *)assetManager.loadAsset<Texture>("Target_UV_done.png");
		if(m_texture == NULL)
		{
			logger.writeToLog("Could not load texture. Quitting");
			GUI::showMessageBox("Could not load texture. Quitting", "Error");
			this->quit();
			return;
		}

		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthMask(GL_TRUE); // turn back on
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
	
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		
		m_program.setVertAttrib("vertex");
		m_program.setDiffuseAttrib("diffuse");
		m_program.setMVPAttrib("mvp");
		m_program.setAmbientAttrib("ambient");
		m_program.setLightAttribs("lightDir", "lightColor");
		m_program.setNormAttrib("normal");
		m_program.setNormMatrixAttrib("normMatrix");
		m_program.setUVAttrib("texCords");
		m_program.setSamplerAttrib("tex");

		m_material.setShader(&m_program);
		m_material.setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));

		
		m_material.setTexture(m_texture);

		m_material.setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
		GameWorld &world = *GameWorld::Instance();
		world.createObject("testObj", 0, 0, 0);
		GameObject &testobj = *world.getObject("testObj");
		modelComp = new ModelComponent(m_model, &m_material);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj.addComponent(modelComp);
		testobj.addComponent(new ScriptComponent("demoTest.lua"));

		m_camera.setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
		m_camera.setTarget(glm::vec3(0.0f));
		//
		RenderManager::set3DMode(45.0f);
		this->getWindow()->show();
		doOnce = true;
	}
	modelComp->setRotation(glm::vec3(0.0f, rotation, 90.0f));
	rotation += 1;
	if(rotation >= 360)
		rotation = 0;

	UserInput input;

	if(input.isMouseKeyPressed(sf::Mouse::Left)) {
		double distance = checkPointDistance(input.getMousePosition());
		cout.precision(dbl::digits10);
		cout<< "distance: " << fixed << distance << endl;
	}
}

double EngDemoApp::checkPointDistance(sf::Vector2i point){
	return sqrt(pow(point.x, 2.0) + pow(point.y, 2.0));
}

void EngDemoApp::render(){
	RenderList &renderList = *RenderList::Instance();
	renderList.renderList(m_camera);
}

void EngDemoApp::shutdown(){
	AssetManager &assetManager = *AssetManager::Instance();
	GameWorld &world = *GameWorld::Instance();
	world.deleteObject("testObj");
	m_program.release();
	assetManager.releaseAsset("demoVert12.vert");
	assetManager.releaseAsset("demoFrag12.frag");
	assetManager.releaseAsset("decocube.obj");
}