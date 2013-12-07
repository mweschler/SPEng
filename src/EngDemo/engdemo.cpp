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

		m_material.setShader(&m_program);

		GameWorld &world = *GameWorld::Instance();
		world.createObject("testObj", 0, 0, 0);
		GameObject &testobj = *world.getObject("testObj");
		testobj.addComponent(new ModelComponent(m_model, &m_material));

		m_camera.setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
		
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

}