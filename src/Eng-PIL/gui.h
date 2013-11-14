#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include <string>

class Window;
class GUI{
public:
	GUI();
	~GUI();
	static void showMessageBox(std::string message, std::string title);
	static Window *createWindow(int width, int height, bool fullscreen);
	static bool initialize();
	static bool isInitialized();
	static void shutdown();
#ifdef _WIN32
	static LPCSTR getAppName();
	static HINSTANCE getHInstance();
#endif
private:
	static bool initialized;
#ifdef _WIN32
	static LPCSTR m_appname;
	static HINSTANCE m_hinstance;

#endif
};
