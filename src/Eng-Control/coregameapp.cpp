#include "gui.h"
#include "coregameapp.h"
#include "window.h"
#include "ConfigurationManager.h"
#include "Logger.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "AudioManager.h"
#include "ScriptingManager.h"
#include "IObserver.h"
#include "GameWorld.h"
#include <sstream>

CoreGameApp::CoreGameApp():
	m_wnd(NULL),
	m_quit(false)
{

}

int CoreGameApp::run(int argc,char *argv[]){
	if(!coreInitialize()){
		coreShutdown();
		return -1;
	}

	Logger &logger = *Logger::Instance();

	logger.writeToLog("Core systems initialized");

	if(!initialize()){
		logger.writeToLog("User systems failed to initialize, shutting down");
		shutdown();
		coreShutdown();
		return -1;
	}

	logger.writeToLog("User systems initialized");

	ConfigurationManager &config = *ConfigurationManager::Instance();
	int width = config.getVariable<int>("w_width");
	int height = config.getVariable<int>("w_height");
	bool fullscreen = config.getVariable<bool>("w_fullscreen");


	m_wnd = GUI::createWindow(width, height, fullscreen);
	
	if(m_wnd == NULL){
		logger.writeToLog("Failed to create window, shutting down");
		shutdown();
		coreShutdown();
		return -1;
	}

	std::stringstream ss;
	ss<<"Window created: ("<<width<<" x "<<height<<")";
	logger.writeToLog(ss.str());


	logger.writeToLog("Staring game loop");
	gameLoop();
	
	logger.writeToLog("Shutting down user systems");
	shutdown();

	logger.writeToLog("Shutting down core systems");
	coreShutdown();

	return 0;
}

void CoreGameApp::quit(){
	Logger &logger = *Logger::Instance();
	logger.writeToLog("Quit command recieved");
	m_quit = true;
}


Window *CoreGameApp::getWindow(){
	return m_wnd;
}

#pragma region UserFunctions
bool CoreGameApp::initialize(){
	//do nothing here, user overrides it
	return true;
}

void CoreGameApp::update(){
	//do nothing here, user overrides it
}

void CoreGameApp::render(){
	//do nothing here, user ovrrides it
}

void CoreGameApp::shutdown(){
}

#pragma endregion


bool CoreGameApp::coreInitialize(){
	Logger &logger = *Logger::Instance();
	logger.initialize();
	
	ConfigurationManager &config = *ConfigurationManager::Instance();
	
	if(!GUI::initialize())
	{
		logger.writeToLog("GUI failed to initialize");
		return false;
	}

	if(!RenderManager::initialize()){
		logger.writeToLog("RenderManager failed to initialize");
		return false;
	}

	AssetManager &assetMgr = *AssetManager::Instance();
	
	ScriptingManager &scripting = *ScriptingManager::Instance();
	
	GameWorld &world = *GameWorld::Instance();

	config.setVariable("g_ms_per_update", 16);
	config.setVariable("g_frameskip", 5);

	return true;
}

void CoreGameApp::coreUpdate(){		
	GameWorld &world = *GameWorld::Instance();
	world.update();
}

void CoreGameApp::coreRender(){
	RenderManager::update();
}

void CoreGameApp::coreShutdown(){
	Logger &logger = *Logger::Instance();

	m_wnd->close();
	delete m_wnd;
	logger.writeToLog("Window closed and deleted");

	RenderManager::shutdown();
	GUI::shutdown();
	
	logger.shutdown();
}

void CoreGameApp::gameLoop(){
	Logger &logger = *Logger::Instance();
	ConfigurationManager &config = *ConfigurationManager::Instance();

	int msPerUpdate = config.getVariable<int>("g_ms_per_update");
	int frameSkip = config.getVariable<int>("g_frameskip");

	while(!m_quit){
		m_wnd->pollEvents();
		if(m_wnd->shouldQuit()){
			logger.writeToLog("Window close message recieved");
			quit();
		}

		coreUpdate();
		update();
		coreRender();
		render();

		m_wnd->swapBuffers();
	}
}