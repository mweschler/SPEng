#include "modelComponent.h"
#include "renderList.h"

ModelComponent::ModelComponent(Model *model, Material *material):
	m_model(model),
	m_material(material)
{
	
}

void ModelComponent::update(){
	RenderList &renderList = *RenderList::Instance();
	renderList.add(m_model, m_material);
}

