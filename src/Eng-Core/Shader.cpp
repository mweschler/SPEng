#include <fstream>
#include <iostream>
#include <sstream>
#include "Shader.h"
#include "Logger.h"
#include "GLHelper.h"
#include "assertions.h"

/*! Initializes a shader object ready for data
*/
Shader::Shader():
	m_shader(0),
	m_type(0),
	m_data(""),
	m_loaded(false),
	m_compiled(false)
{

}

/*! Sets the type of shader for this object
	\param type Eiter GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
*/
void Shader::setType(GLenum type){
	if(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
		this->m_type = type;
	else
	{
		Logger &logger = *Logger::Instance();
		logger.writeToLog("Shader.setType failed! invalid parameter");
	}
}

/*! Gets the type for this shader
	\return the current type of GL Shader
*/
GLenum Shader::getType(){
	return this->m_type;
}

/*! Compiles the shader for use in a shader program
	\return true on success, false otherwise
*/
bool Shader::compile(){
	GLHelper::flushGLErrors();

	if(m_shader != 0)
		return false;

	if(!(m_type == GL_VERTEX_SHADER || m_type == GL_FRAGMENT_SHADER)){
		return false;
	}

	const char *data = m_data.c_str();


	GLuint shader = glCreateShader(m_type);
	GLenum error = glGetError();
	if(error == GL_INVALID_ENUM)
	{
		Logger &logger = *Logger::Instance();
		logger.writeToLog("Error creating shader: GL_INVALID_ENUM");
		return false;
	}

	glShaderSource(shader, 1, &data, NULL);
	error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error with shader source: ";

		msg = msg + GLHelper::errorEnumToString(error);

		Logger &logger =  *Logger::Instance();
		logger.writeToLog(msg);

		return false;
	}

	glCompileShader(shader);
	error = glGetError();
	if(error != GL_NO_ERROR){
		std::string msg = "Error compiling shader source: ";

		msg = msg + GLHelper::errorEnumToString(error);

		Logger &logger =  *Logger::Instance();
		logger.writeToLog(msg);

		return false;
	}

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE){
		GLint logLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *log = new GLchar[logLength + 1];

		glGetShaderInfoLog(shader, logLength, NULL, log);
		log[logLength] = '\0';

		std::stringstream ss;
		ss<<"Failed to compile shader "<<log;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(ss.str());
		std::cout<<ss.str()<<std::endl;
		delete[] log;
		glDeleteShader(shader);

		return false;
	}

	m_shader = shader;
	m_compiled = true;
	return true;
}

/*! Gets the compilation status
	\return ture if compiled, false otherwise
*/
bool Shader::isCompiled(){
	return this->m_compiled;
}


/*! Tells if the data has been loaded or not
	\return ture if loaded, false otherwise
*/
bool Shader::isLoaded(){
	return this->m_loaded;
}

/*! Gets the OpenGL ID for this shader
	\return the ID of the shader
*/
GLuint Shader::getID(){
	return this->m_shader;
}

/*! Loads the shader data from a file
	\param filename The location and name of the file to load
	\return ture if succesfully loaded into local memory
*/
bool Shader::load(std::string filename){
	ASSERT(filename.length() > 0)
	std::ifstream file;
	std::stringstream stream;
	file.open(filename, std::ios::in);

	if(!file.is_open()){
		std::stringstream ss;
		ss<<"Could not open shader file "<<filename;
		Logger &logger = *Logger::Instance();
		logger.writeToLog(ss.str());
		return false;
	}

	stream << file.rdbuf();
	file.close();
	m_data = stream.str();
	m_loaded = true;
	return true;
}

void Shader::loadFromString(std::string data){
	m_data= data;
	m_loaded = true;
}

Shader::~Shader(){

}

/*! Releases the shader from OpenGL
	\return true if the shader was released from memory
*/
bool Shader::release(){
	if(!(m_loaded && m_compiled))
		return false;
	ASSERT(m_shader != 0);
	glDeleteShader(m_shader);
	m_compiled = false;
	m_shader = 0;

	return true;
}

