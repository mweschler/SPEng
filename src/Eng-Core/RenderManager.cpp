#include "RenderManager.h"
#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"
#include "Camera.h"

static RenderInternal render;


bool RenderManager::initialize(){
	return render.initialize();
}

bool RenderManager::isInitialized(){
	return render.isInitialized();
}

void RenderManager::shutdown(){
	render.shutdown();
}

void RenderManager::drawModel(const Model model,const Material material, const Camera camera, glm::mat4 transform){
	render.drawModel(model, material, camera, transform);
}

void RenderManager::update(){
	render.update();
}

void RenderManager::set3DMode(float fov){
	render.set3DMode(fov);
}

void RenderManager::setViewport(int x, int y, int width, int height){
	render.setViewPort(x,y,width,height);
}

void RenderManager::setGlobalLight(glm::vec3 direction, glm::vec4 color){
	render.setGlobalLight(direction, color);
}

void RenderManager::setAmbient(glm::vec4 intensity){
	render.setAmbient(intensity);
}