#include <iostream>
#include <string>
#include "GLHelper.h"
#include "GL\glew.h"
#include "Logger.h"

<<<<<<< HEAD
public void GLHelper::flushGLErrors(){
=======
void GLHelper::flushGLErrors(){
>>>>>>> ab0f03b05b9dd2e579e0f7756d6e96a6b02fd5e7
	
	GLenum rv = glGetError();
	if(rv != GL_NO_ERROR)
	{
		Logger &logger = *Logger::Instance();
		std::string msg = "Unhandled GL ERROR found! Error number: " + rv;
		logger.writeToLog(msg);
		std::cout<<msg<<std::endl;
	}
}
