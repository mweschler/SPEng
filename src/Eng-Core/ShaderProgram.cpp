#include <sstream>
#include <iostream>
#include "ShaderProgram.h"
#include "Shader.h"
#include "GLHelper.h"
#include "Logger.h"

ShaderProgram::ShaderProgram():
	m_linked(false),
	m_program(0)
{

}

ShaderProgram::~ShaderProgram(){

}

bool ShaderProgram::use(){
	if(m_program == 0  || m_linked == false)
		return false;

	glUseProgram(m_program);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Could not use shader program: " + GLHelper::errorEnumToString(error);
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);

		return false;
	}

	return true;
}

bool ShaderProgram::link(Shader &vertexShader, Shader &fragmentShader){
	if(vertexShader.isCompiled() == false || fragmentShader.isCompiled() == false)
	{
		std::cout<<"Shaders not compiled"<<std::endl;
		return false;
	}

	if(vertexShader.getType() != GL_VERTEX_SHADER || fragmentShader.getType() != GL_FRAGMENT_SHADER)
	{
		std::cout<<"Shader of wrong type"<<std::endl;
		return false;
	}

	GLHelper::flushGLErrors();

	GLuint program = glCreateProgram();
	if(program == 0)
		return false;

	glAttachShader(program, vertexShader.getID());
	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error adding vertex Shader: ";

		msg = msg + GLHelper::errorEnumToString(error);
		
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);
		return false;
	}

	glAttachShader(program, fragmentShader.getID());
	error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error adding fragment Shader: ";

		msg = msg + GLHelper::errorEnumToString(error);
		std::cout<<msg<<std::endl;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);
		return false;
	}

	glLinkProgram(program);
	error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error linking program: ";

		msg = msg + GLHelper::errorEnumToString(error);
		std::cout<<msg<<std::endl;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);

		glDetachShader(program, vertexShader.getID());
		glDetachShader(program, fragmentShader.getID());

		return false;
	}

	glDetachShader(program, vertexShader.getID());
	glDetachShader(program, fragmentShader.getID());

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error getting link status: ";

		msg = msg + GLHelper::errorEnumToString(error);
		std::cout<<msg<<std::endl;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);

		return false;
	}

	if(status == GL_FALSE){
		GLint logLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *log = new GLchar[logLength + 1];

		glGetProgramInfoLog(program, logLength, NULL, log);
		log[logLength] = '\0';

		std::stringstream ss;
		ss<<"Failed to link program"<<std::endl<<log;
		std::cout<<ss.str()<<std::endl;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(ss.str());

		delete[] log;
			
		glDeleteProgram(program);
		return false;
	}

	m_program = program;
	m_linked = true;

	return true;
}

bool ShaderProgram::isLinked(){
	return m_linked;
}

bool ShaderProgram::release(){
	if(m_linked == false || m_program == 0)
		return false;

	GLHelper::flushGLErrors();

	glDeleteProgram(m_program);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error deleting program: ";
		msg = msg + GLHelper::errorEnumToString(error);
		Logger &logger = *Logger::Instance();
		logger.writeToLog(msg);

		return false;
	}

	m_program = 0;

	return true;
}