#include <iostream>
#include <string>
#include "GLHelper.h"
#include "GL\glew.h"
#include "Logger.h"


void GLHelper::flushGLErrors(){

	
	GLenum rv = glGetError();
	if(rv != GL_NO_ERROR)
	{
		Logger &logger = *Logger::Instance();
		std::string msg = "Unhandled GL ERROR found! Error number: " + rv;
		logger.writeToLog(msg);
		std::cout<<msg<<std::endl;
	}
}

std::string GLHelper::errorEnumToString(GLenum error){
	std::string msg = "";

	switch(error){
		case GL_INVALID_VALUE: msg = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: msg = "GL_INVALID_OPERATION"; break;
		default: msg = "Other error";
		}

	return msg;
}
