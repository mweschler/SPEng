#ifdef _WIN32
#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/GL.h>
#endif
#include "window.h"
#include "gui.h"
#include "assertions.h"



Window::Window()
	:m_width(800)
	,m_height(600)
	,m_fullscreen(false)
	,m_colorBits(32)
	,m_depthBits(24)
	,m_stencilBits(8)
	,m_doubleBuffer(true)
	,m_quit(false)
	,m_clean(true)
	,m_majorVersion(0)
	,m_minorVersion(0)
{

}

Window::~Window(){
	//if(!m_clean)
	//	this->close();
}

//TODO: Have it resize window after creation
void Window::setDimensions(int width, int height){
	ASSERT((width > 0) && (height > 0));
	this->m_width = width;
	this->m_height = height;
}

//TODO: Have it toggle after creation
void Window::setFullscreen(bool fullscreen){
	this->m_fullscreen = fullscreen;
	if(fullscreen){
#ifdef _WIN32

#endif
	}
	else{
#ifdef _WIN32
#endif
	}
}

bool Window::create(){
	ASSERT(GUI::isInitialized());
#ifdef _WIN32
	this->m_hinstance = GUI::getHInstance();
	this->m_appname = GUI::getAppName();

	int posX = 0, posY = 0;
	DWORD style = WS_POPUP;
	if(this->m_fullscreen){
		DEVMODE screenSettings;

		memset(&screenSettings, 0, sizeof(screenSettings));
		screenSettings.dmSize = sizeof(screenSettings);
		screenSettings.dmPelsWidth = m_width;
		screenSettings.dmPelsHeight = m_height;
		screenSettings.dmBitsPerPel = m_colorBits;
		screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN);

	} else{ //Windowed mode, center the winodw
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_height) / 2;
		style = style | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ;
	}

	this->m_handle = CreateWindowEx(WS_EX_APPWINDOW, m_appname, m_appname,
		style, posX, posY, m_width, m_height, NULL, NULL, this->m_hinstance,NULL);

	if(m_handle == NULL){
		std::cout<<"Window handle was null!"<<std::endl;
		return false;
	}

	this->m_clean = false;

	//setup devicecontext and render context;

	HDC dc = GetDC(m_handle);
	if(!dc){
		std::cout<<"Could not get device context"<<std::endl;
		return false;
	}

	m_deviceContext.setHandle(dc);

	int attribList[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, m_doubleBuffer,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, m_colorBits,
		WGL_DEPTH_BITS_ARB, m_depthBits,
		WGL_STENCIL_BITS_ARB, m_stencilBits,
		0,
	};

	int pixelFormat = 0;
	UINT numFormats;

	if(!(wglChoosePixelFormatARB(dc, attribList, NULL, 1, &pixelFormat, &numFormats))){
		std::cout<<"Could not choose pixel format"<<std::endl;
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelDescriptor;

	if(!SetPixelFormat(dc, pixelFormat, &pixelDescriptor)){
		std::cout<<"Could not set pixel format"<<std::endl;
		return false;
	}
	HGLRC rc;
	if(!WGLEW_ARB_create_context_profile){
		rc = wglCreateContext(dc);
		if(!rc){
			DWORD errnum = GetLastError();
			std::cout<<"Could not create render context, Error #: "<<errnum<<std::endl;
			return false;
		}
	} else{
		attribList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
		attribList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
		attribList[4] = 0;

		if(GLEW_VERSION_4_0){
			attribList[1] = 4;
			attribList[3] = 0;
			m_majorVersion = 4;
			m_minorVersion = 0;
			std::cout<<"OpenGL version 4.0 support detected"<<std::endl;
		}else if(GLEW_VERSION_3_0){
			attribList[1] = 3;
			attribList[3] = 0;
			m_majorVersion = 3;
			m_minorVersion = 0;
			std::cout<<"OpenGL version 3.0 support detected"<<std::endl;
		} else if(GLEW_VERSION_2_1){
			attribList[1] = 2;
			attribList[3] = 1;
			m_majorVersion = 2;
			m_minorVersion = 1;
			std::cout<<"OpenGL version 2.1 support detected"<<std::endl;
		} else{
			std::cout<<"OpenGL version 2.1 or higher is required"<<std::endl;
			return false;
		}

		rc = wglCreateContextAttribsARB(dc, 0, attribList);
		if(rc == NULL){
			std::cout<<"Could not create render context"<<std::endl;
		}
	}

	m_renderContext.setHandle(rc);

	wglMakeCurrent(dc, rc);

	//initilize extensions
	GLenum error = glewInit();
	if(error != GLEW_OK)
		return false;

	return true;
#endif

}

void Window::show(){
#ifdef _WIN32
	ASSERT(m_handle != NULL);
	ShowWindow(m_handle, SW_SHOW);
	SetForegroundWindow(m_handle);
	SetFocus(m_handle);
#endif
}

void Window::swapBuffers(){
#ifdef _WIN32
	SwapBuffers(m_deviceContext.getHandle());
#endif
}

void Window::close(){
#ifdef _WIN32
	if(m_renderContext.getHandle()){
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderContext.getHandle());
		m_renderContext.setHandle(NULL);
	}

	if(m_deviceContext.getHandle()){
		ReleaseDC(m_handle, m_deviceContext.getHandle());
		m_deviceContext.setHandle(NULL);
	}

	ShowCursor(true);

	if(m_fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_handle);

	m_handle = NULL;
	m_appname = NULL;

	m_clean = true;
#endif
}

void Window::showCursor(bool show){
#ifdef _WIN32
	ShowCursor(show);
#endif
}

//Redundent if setFullScreen works post creation
void Window::changeFullscreen(bool full){

}

void Window::setColorBits(int bits){
	ASSERT(bits>0);
	this->m_colorBits = bits;
}

void Window::setDepthBits(int bits){
	ASSERT(bits > 0);
	this->m_depthBits = bits;
}

void Window::setStencilBits(int bits){
	ASSERT(bits > 0);
	this->m_stencilBits = bits;
}

void Window::setDoubleBuffer(bool doubleBuffer){
	this->m_doubleBuffer = doubleBuffer;
}

//Should be called every core loop
void Window::pollEvents(){
#ifdef _WIN32
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(msg.message == WM_QUIT){
		this->m_quit = true;
	}
#endif
}

bool Window::shouldQuit(){
	return this->m_quit;
}

void Window::makeContextCurrent(){
#ifdef _WIN32
	wglMakeCurrent(m_deviceContext.getHandle(), m_renderContext.getHandle());
#endif
}

int Window::getMajorVersion(){
	return m_majorVersion;
}

int Window::getMinorVersion(){
	return m_minorVersion;
}

#ifdef _WIN32
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam){
	switch(umsg){
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN: //Need to record the keys here
	case WM_KEYUP:
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}
#endif

