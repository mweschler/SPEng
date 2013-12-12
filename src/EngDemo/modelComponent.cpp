#include "modelComponent.h"
#include "renderList.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

ModelComponent::ModelComponent(Model *model, Material *material):
	m_model(model),
	m_material(material),
	m_rotation(1.0f)
{
	this->_name = "ModelComponent";
}

void ModelComponent::update(){
	RenderList &renderList = *RenderList::Instance();
	coord loc = *this->getParent()->getLocation();
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(loc.x, loc.y, loc.z));
	transform = transform * m_rotation;
	renderList.add(m_model, m_material, transform);
}


void ModelComponent::setRotation(glm::vec3 rotation){
	m_rotation = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_rotation = glm::rotate(m_rotation, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_rotation = glm::rotate(m_rotation, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

