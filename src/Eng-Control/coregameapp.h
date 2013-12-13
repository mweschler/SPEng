#pragma once

class Window;

/*! The foundation of a game application. To be inherited from. */
class CoreGameApp{
public:
	CoreGameApp();
	/*! Runs the application
		\param argc the number of arguments passed in argv
		\param argv the arguments to the application
		\return the exit status of the application
	*/
	int run(int argc, char *argv[]);
	/*! Tells the application to quit
	*/
	void quit();
	/*! Gets the window for this application
		\return a pointer to the window for this application
	*/
	Window *getWindow();
protected:
	/*! This function, is for the user to initialize their subsystems
		\return success or failure
	*/
	virtual bool initialize();
	/*! It is for the user to have their update steps done durring the game loop*/
	virtual void update();
	/*! This function is called as part of the users render step of the game loop*/
	virtual void render();
	/*! This user function is called for them to shutdown their subsystems*/
	virtual void shutdown();
private:
	/*! runs the game loop that runs untill quit is called*/
	void gameLoop();
	/*! initializes the core subsystems 
		\return success or failure
	*/
	bool coreInitialize();
	/*! does the core update steps for the game loop */
	void coreUpdate();
	/*! does the core render step for the game loop */
	void coreRender();
	/*! does the core shutdown step for the game loop */
	void coreShutdown();

	/*! The window for this application */
	Window *m_wnd;

	/*! the quit state for this application */
	bool m_quit;
};