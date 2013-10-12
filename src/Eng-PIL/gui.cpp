#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#endif

#include <string>
#include "gui.h"
#include "window.h"

bool GUI::initialized = false;
#ifdef _WIN32
LPCSTR GUI::m_appname;
HINSTANCE GUI::m_hinstance;
#define GLEW_STATIC
#endif

GUI::GUI(){

}

GUI::~GUI(){

}

//Shows a message box with message and title
void GUI::showMessageBox(std::string message, std::string title){
#ifdef _WIN32 
	/*TCHAR msg_w[2048], title_w[2048];


	mbstowcs(msg_w, message, size);

	size = strlen(title) +1;

	if(size > 2048)
	size = 2048;

	mbstowcs(title_w, title, size);
	*/

	MessageBox(NULL, message.c_str(), title.c_str(), MB_OK);

#endif
}

//creates a window
Window *GUI::createWindow(int width, int height, bool fullscreen){
	Window *window = new Window();
	window->setDimensions(width, height);
	window->setFullscreen(fullscreen);
	if(!window->create()){
		GUI::showMessageBox(TEXT("Could not create window!"), TEXT("Error"));
	}
	return window;
}
bool GUI::initialize(){
	if(GUI::initialized){
		return true;
	}
#ifdef _WIN32
	//setup window class
	GUI::m_hinstance = GetModuleHandle(NULL);
	GUI::m_appname = "MEng";

	WNDCLASSEX winclass;
	winclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winclass.lpfnWndProc = WndProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = GUI::m_hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winclass.hIconSm = winclass.hIcon;
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = GUI::m_appname;
	winclass.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&winclass);

	//create dummy window for extension loading
	int posX = 0, posY = 0;

	HWND handle = CreateWindowEx(WS_EX_APPWINDOW, GUI::m_appname, GUI::m_appname,
		WS_POPUP, posX, posY, 640, 480, NULL, NULL, GUI::m_hinstance,NULL);

	if(handle == NULL){
		//std::cout<<"Window handle was null!"<<std::endl;
		return false;
	}
	//make sure window is hidden
	ShowWindow(handle, SW_HIDE);

	//setup devicecontext and render context;

	HDC dc = GetDC(handle);
	if(!dc){
		//std::cout<<"Could not get device context"<<std::endl;
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelDescriptor={
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = 0;
	pixelFormat = ChoosePixelFormat(dc, &pixelDescriptor);
	if(!pixelFormat){
		//std::cout<<"Could not choose pixel format"<<std::endl;
		return false;
	}

	if(!SetPixelFormat(dc, pixelFormat, &pixelDescriptor)){
		//std::cout<<"Could not set pixel format"<<std::endl;
		return false;
	}

	HGLRC rc = wglCreateContext(dc);
	if(!rc){
		//DWORD errnum = GetLastError();
		//std::cout<<"Could not create render context, Error #: "<<errnum<<std::endl;
		return false;
	}

	wglMakeCurrent(dc, rc);

	//initilize extensions
	GLenum error = glewInit();
	if(error != GLEW_OK)
		return false;

	//get rid of contexts and window
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(rc);
	ReleaseDC(handle, dc);
	DestroyWindow(handle);
#endif

	initialized = true;
	return true;
}

bool GUI::isInitialized(){
	return GUI::initialized;
}

void GUI::shutdown(){
	UnregisterClass(GUI::m_appname, GUI::m_hinstance);
	GUI::m_appname = NULL;
	GUI::m_hinstance = NULL;
	GUI::initialized = false;
}

#ifdef _WIN32
LPCSTR GUI::getAppName(){
	return GUI::m_appname;
}

HINSTANCE GUI::getHInstance(){
	return GUI::m_hinstance;
}
#endif
