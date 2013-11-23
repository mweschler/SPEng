#pragma once

class Window;

class CoreGameApp{
public:
	CoreGameApp();
	int run(int argc, char *argv[]);
	void quit();
	Window *getWindow();
protected:
	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void shutdown();
private:
	void gameLoop();
	bool coreInitialize();
	void coreUpdate();
	void coreRender();
	void coreShutdown();

	Window *m_wnd;
	bool m_quit;
};