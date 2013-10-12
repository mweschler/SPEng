#pragma once

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")

#include <Windows.h>
#endif



class DeviceContext{
public:
	DeviceContext();
	~DeviceContext();
#ifdef _WIN32
	HDC getHandle();
	void setHandle(HDC handle);
#endif
private:
#ifdef _WIN32
	HDC m_dc;
#endif
};

class RenderContext{
public:
	RenderContext();
	~RenderContext();
#ifdef _WIN32
	HGLRC getHandle();
	void setHandle(HGLRC handle);
#endif
private:
#ifdef _WIN32
	HGLRC m_rc;
#endif
};

class Window{
public:
	Window();
	~Window();
	void setDimensions(int width, int height);
	void setFullscreen(bool fullscreen);
	void setColorBits(int bits);
	void setDepthBits(int bits);
	void setStencilBits(int bits);
	void setDoubleBuffer(bool doubleBuffer);
	bool create();
	void show();
	void showCursor(bool show);
	void pollEvents();
	bool shouldQuit();
	void makeContextCurrent();
	void swapBuffers();
	void close();
	int getMajorVersion();
	int getMinorVersion();

private:
	void changeFullscreen(bool full);
	unsigned long m_width;
	unsigned long m_height;
	bool m_fullscreen;
	int m_colorBits;
	int m_depthBits;
	int m_stencilBits;
	bool m_doubleBuffer;
	bool m_quit;
	DeviceContext m_deviceContext;
	RenderContext m_renderContext;
	bool m_clean;
	int m_majorVersion;
	int m_minorVersion;
#ifdef _WIN32
	HWND m_handle;
	HINSTANCE m_hinstance;
	LPCSTR m_appname;
#endif
};
#ifdef _WIN32
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif



