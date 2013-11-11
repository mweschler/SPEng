#include "RenderManager.h"
#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"

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

void RenderManager::drawModel(const Model model,const Material material){
	render.drawModel(model, material);
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