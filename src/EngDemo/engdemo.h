#include "coregameapp.h"

class EngDemoApp: public CoreGameApp{
public:
	EngDemoApp();
protected:
	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void shutdown();
};