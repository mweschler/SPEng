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
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ConfigurationManager.h"


static bool doOnce = false;

void rotateObjects(std::vector<ModelComponent *> objects);


EngDemoApp::EngDemoApp():
	m_texture(NULL)
{

}

bool EngDemoApp::initialize(){
	ConfigurationManager &config = *ConfigurationManager::Instance();
	config.setVariable<int> ("w_width", 1600);
	config.setVariable<int> ("w_height", 900);
	config.setVariable<bool> ("w_fullscreen", true);
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

		m_model->setModelMatrix(glm::scale(glm::vec3(2.5f, 2.5f, 2.5f)));

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

		//setup background quad
		m_backdrop = (Texture *)assetManager.loadAsset<Texture>("cat_diff.tga");
		if(m_backdrop == NULL){
			logger.writeToLog("Could not load backdrop. Quitting");
			GUI::showMessageBox("Could not load backdrop. Quitting", "Error");
			this->quit();
			return;
		}

		m_quad = (Model *) assetManager.loadAsset<Model>("quad.obj");
		if(m_quad == NULL)
		{
			logger.writeToLog("Could not load quad. Quitting");
			GUI::showMessageBox("Could not load	quad. Quitting", "Error");
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

		world.createObject("testObj1", 0, 3, 0);
		world.createObject("testObj2", 0, 3, 7);
		world.createObject("testObj3", 0, 3, -7);
		world.createObject("testObj4", 0, -3, 7);
		world.createObject("testObj5", 0, -3, 0);
		world.createObject("testObj6", 0, -3, -7);

		GameObject &testobj = *world.getObject("testObj1");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj.addComponent(modelComp);
		

		m_rotating.push_back(modelComp);

		GameObject &testobj2 = *world.getObject("testObj2");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj2.addComponent(modelComp);

		m_rotating.push_back(modelComp);

		GameObject &testobj3 = *world.getObject("testObj3");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj3.addComponent(modelComp);
		
		m_rotating.push_back(modelComp);

		GameObject &testobj4 = *world.getObject("testObj4");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj4.addComponent(modelComp);
		m_rotating.push_back(modelComp);

		GameObject &testobj5 = *world.getObject("testObj5");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj5.addComponent(modelComp);

		m_rotating.push_back(modelComp);

		GameObject &testobj6 = *world.getObject("testObj6");
		modelComp = new ModelComponent(m_model, &m_material);
		m_components.push_back(modelComp);

		//m_model->setModelMatrix(glm::translate(glm::mat4(1.0f), -0.5f, -0.5f, -0.5f));
		modelComp->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));

		testobj6.addComponent(modelComp);

		m_camera.setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
		m_camera.setTarget(glm::vec3(0.0f));
		//
		RenderManager::set3DMode(70.0f);
		this->getWindow()->show();
		doOnce = true;
	}

	rotateObjects(m_rotating);
}

void rotateObjects(std::vector<ModelComponent *> objects){
	for(auto object  = objects.begin(); object != objects.end();)
	{
		glm::vec3 objRotation = (*object)->getRotation();
		objRotation.y += 1;

		if(objRotation.y >= 360)
			object = objects.erase(object);
		else{
			(*object)->setRotation(objRotation);
			++object;
		}
	}
}


void EngDemoApp::render(){
	RenderList &renderList = *RenderList::Instance();
	renderList.renderList(m_camera);
}

void EngDemoApp::shutdown(){
	AssetManager &assetManager = *AssetManager::Instance();
	GameWorld &world = *GameWorld::Instance();
	world.deleteObject("testObj1");
	world.deleteObject("testObj2");
	world.deleteObject("testObj3");
	m_program.release();
	assetManager.releaseAsset("demoVert12.vert");
	assetManager.releaseAsset("demoFrag12.frag");
	assetManager.releaseAsset("decocube.obj");
}