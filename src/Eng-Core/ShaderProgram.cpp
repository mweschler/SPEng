#include <sstream>
#include <iostream>
#include "ShaderProgram.h"
#include "Shader.h"
#include "GLHelper.h"
#include "Logger.h"

ShaderProgram::ShaderProgram():
	m_linked(false),
	m_program(0),
	m_diffAttrib(""),
	m_vertAttrib(""),
	m_normAttrib(""),
	m_MVPAttrib(""),
	m_lightDir(""),
	m_lightColor(""),
	m_ambient(""),
	m_normMatrix("")
{

}

ShaderProgram::~ShaderProgram(){

}

bool ShaderProgram::use() const{
	if(m_program == 0  || m_linked == false)
		return false;
	
	GLHelper::flushGLErrors();
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

bool ShaderProgram::isLinked() const{
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
	m_linked = false;

	return true;
}

GLuint ShaderProgram::getID() const{
	return m_program;
}

void ShaderProgram::setDiffuseAttrib(std::string name){
	m_diffAttrib = name;
}

std::string ShaderProgram::getDiffuseAttrib() const{
	return m_diffAttrib;
}

void ShaderProgram::setVertAttrib(std::string name){
	m_vertAttrib = name;
}

std::string ShaderProgram::getVertAttrib() const{
	return m_vertAttrib;
}

void ShaderProgram::setNormAttrib(std::string name){
	m_normAttrib = name;
}

std::string ShaderProgram::getNormAttrib() const{
	return m_normAttrib;
}

void ShaderProgram::setMVPAttrib(std::string name){
	m_MVPAttrib = name;
}

std::string ShaderProgram::getMVPAttrib() const{
	return m_MVPAttrib;
}

void ShaderProgram::setLightAttribs(std::string dir, std::string color){
	m_lightDir = dir;
	m_lightColor = color;
}

std::string ShaderProgram::getLightDirAttrib() const{
	return m_lightDir;
}

std::string ShaderProgram::getLightColorAttrib() const{
	return m_lightColor;
}

void ShaderProgram::setAmbientAttrib(std::string name){
	m_ambient = name;
}

std::string ShaderProgram::getAmbientAttrib() const{
	return m_ambient;
}

void ShaderProgram::setNormMatrixAttrib(std::string name){
	m_normMatrix = name;
}

std::string ShaderProgram::getNormMatrixAttrib() const {
	return m_normMatrix;
}