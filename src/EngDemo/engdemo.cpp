#include "engdemo.h"
#include "window.h"

static bool doOnce = false;

EngDemoApp::EngDemoApp(){

}

bool EngDemoApp::initialize(){
	return true;
}

void EngDemoApp::update(){
	if(!doOnce)
	{
		this->getWindow()->show();
		doOnce = true;
	}
}

void EngDemoApp::render(){

}

void EngDemoApp::shutdown(){

}