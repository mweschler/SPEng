#include "modelComponent.h"
#include "renderList.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

ModelComponent::ModelComponent(Model *model, Material *material):
	m_model(model),
	m_material(material)
{
	this->_name = "ModelComponent";
}

void ModelComponent::update(){
	RenderList &renderList = *RenderList::Instance();
	coord loc = *this->getParent()->getLocation();
	glm::mat4 transform = glm::translate(glm::vec3(loc.x, loc.y, loc.z));
	
	renderList.add(m_model, m_material, transform);
}

