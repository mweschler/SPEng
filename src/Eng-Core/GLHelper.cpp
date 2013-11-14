#include <iostream>
#include <string>
#include <sstream>
#include "GLHelper.h"
#include "GL\glew.h"
#include "Logger.h"


void GLHelper::flushGLErrors(){

	
	GLenum rv = glGetError();
	if(rv != GL_NO_ERROR)
	{
		Logger &logger = *Logger::Instance();
		std::stringstream ss;
		ss<<"Unhandled GL ERROR found! Error number: ";
		ss<<rv;
		ss<<" Name: "<<errorEnumToString(rv);
		logger.writeToLog(ss.str());
		//std::cout<<ss.str()<<std::endl;
	}
}

std::string GLHelper::errorEnumToString(GLenum error){
	std::string msg = "";

	switch(error){
		case GL_INVALID_VALUE: msg = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: msg = "GL_INVALID_OPERATION"; break;
		case GL_INVALID_ENUM: msg = "GL_INVALID_ENUM"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: msg = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		case GL_OUT_OF_MEMORY: msg = "GL_OUT_OF_MEMORY"; break;
		case GL_STACK_UNDERFLOW: msg = "GL_STACK_UNDERFLOW"; break;
		case GL_STACK_OVERFLOW: msg = "GL_STACK_OVERFLOW"; break;
		default: msg = "Other error";
		}

	return msg;
}
