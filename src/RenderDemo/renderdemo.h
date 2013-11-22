#pragma once
#include "coregameapp.h"

class RenderDemoApp : public CoreGameApp{
protected:
	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void shutdown();
};
