#include "renderList.h"
#include <RenderManager.h>
#include <iostream>

static RenderList *s_instance = NULL;

RenderList::RenderList(){
	
}

RenderList *RenderList::Instance(){
	if(s_instance == NULL)
		s_instance = new RenderList();

	return s_instance;
}

void RenderList::update(){

}

void RenderList::renderList(Camera camera){
	for(int i = 0; i < m_objects.size(); ++i){
		RenderObject obj = m_objects[i];
		RenderManager::drawModel(*obj.model, *obj.material, camera, obj.transform);
		//std::cout<<"Rendered an object\n";
	}

	

	m_objects.clear();
}

void RenderList::add(Model *model, Material *material, glm::mat4 transform){
	RenderObject obj;
	obj.model = model;
	obj.material = material;
	obj.transform = transform;

	//std::cout<<"Added to list\n";

	m_objects.push_back(obj);
}