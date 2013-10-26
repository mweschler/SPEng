#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"

RenderInternal::RenderInternal():
	m_initialized(false)
{

}

bool RenderInternal::initialize(){
	if(this->m_initialized == true)
		return false;

	this->m_initialized = true;
	return true;
}

bool RenderInternal::isInitialized(){
	return m_initialized;
}

void RenderInternal::shutdown(){
	this->m_initialized = false;
}

void RenderInternal::update(){}

void RenderInternal::drawModel(Model model, Material material){}