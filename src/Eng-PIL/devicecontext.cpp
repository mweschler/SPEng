#include "window.h"


	DeviceContext::DeviceContext(){
#ifdef _WIN32
		this->m_dc = NULL;
#endif
	}

	DeviceContext::~DeviceContext(){
	}

#ifdef _WIN32
	HDC DeviceContext::getHandle(){
		return this->m_dc;
	}

	void DeviceContext::setHandle(HDC handle){
		this->m_dc = handle;
	}

#endif
