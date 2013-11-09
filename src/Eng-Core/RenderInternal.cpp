#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"
//#include "Logger.h"

//static Logger *logger;
RenderInternal::RenderInternal():
	m_initialized(false)
{
	//logger = Logger::Instance();
	//logger->initialize();
	//logger->createLog();
}

bool RenderInternal::initialize(){
	if(this->m_initialized == true)
		return false;
	
	this->m_initialized = true;
	//logger->writeToLog("Render System initialized");
	return true;
}

bool RenderInternal::isInitialized()
{
	return m_initialized;
}

void RenderInternal::shutdown(){
	this->m_initialized = false;
	//logger->writeToLog("Render System Shutdown");
}

void RenderInternal::update(){}

void RenderInternal::drawModel(const Model model, const Material material){

}