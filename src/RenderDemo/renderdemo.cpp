#include "renderdemo.h"
#include "window.h"

static bool once = false;

bool RenderDemoApp::initialize(){
	return true;
}

void RenderDemoApp::update(){
	if(!once)
	{
		Window &wnd = *this->getWindow();
		wnd.show();
	}
}

void RenderDemoApp::render(){

}

void RenderDemoApp::shutdown(){

}