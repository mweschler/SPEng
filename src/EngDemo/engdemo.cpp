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

static bool doOnce = false;

EngDemoApp::EngDemoApp(){

}

bool EngDemoApp::initialize(){

	return true;
}

void EngDemoApp::update(){
	Logger &logger = *Logger::Instance();

	if(!doOnce)
	{
		AssetManager &assetManager = *AssetManager::Instance();
		m_model = (Model *)assetManager.loadAsset<Model>("decocube.obj");
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
		//
		m_program.setVertAttrib("vertex");
		m_program.setMVPAttrib("mvp");

		m_material.setShader(&m_program);

		GameWorld &world = *GameWorld::Instance();
		world.createObject("testObj", 0, 10, 0);
		GameObject &testobj = *world.getObject("testObj");
		ModelComponent *modelComp = new ModelComponent(m_model, &m_material);
		
		testobj.addComponent(modelComp);
		testobj.addComponent(new ScriptComponent("demoTest.lua"));

		m_camera.setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
		m_camera.setTarget(glm::vec3(0.0f));
		
		RenderManager::set3DMode(45.0f);
		this->getWindow()->show();
		doOnce = true;
	}
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