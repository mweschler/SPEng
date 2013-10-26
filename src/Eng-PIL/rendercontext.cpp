#include "window.h"


	RenderContext::RenderContext(){
#ifdef _WIN32
		this->m_rc = NULL;
#endif
	}

	RenderContext::~RenderContext(){

	}

#ifdef _WIN32
	HGLRC RenderContext::getHandle(){
		return this->m_rc;
	}

	void RenderContext::setHandle(HGLRC handle){
		this->m_rc = handle;
	}
#endif
