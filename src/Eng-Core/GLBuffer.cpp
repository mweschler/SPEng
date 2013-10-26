#include <GL/glew.h>
#include "GLBuffer.h"
#include "assertions.h"

#include <iostream>

GLBuffer::GLBuffer(GLenum type):
	m_type(type),
	m_buffer(0)
{
}

GLBuffer::GLBuffer(){
	ASSERT(false); //should never get here
}

bool GLBuffer::bind() const{
	if(glIsBuffer(m_buffer) == GL_TRUE){
		//log error
		std::cout<<"DEBUG: m_buffer is already bound"<<std::endl;
		return false;
	}

	glBindBuffer(m_type, m_buffer);
	GLenum error = glGetError();
	if(error == GL_INVALID_ENUM){
		//log error
		std::cout<<"DEBUG: bind buffer gave invalid enum"<<std::endl;
		return false;
	}
	if(error == GL_INVALID_VALUE){
		//log error
		std::cout<<"DEBUG: bind buffer gave invalid value"<<std::endl;
		return false;
	}

	return true;
}

bool GLBuffer::create(){
	if(glIsBuffer(m_buffer) == GL_TRUE){
		//log error
		return false;
	}
	
	GLuint buff;
	glGenBuffers(1, &buff);
	if(glGetError() == GL_INVALID_VALUE)
		return false;

	m_buffer = buff;
	return true;
}

GLenum GLBuffer::getType() const{
	return this->m_type;
}

bool GLBuffer::release(){
	if(glIsBuffer(m_buffer) == GL_FALSE){
		//log error
		return false;
	}

	glDeleteBuffers(1, &m_buffer);
	GLenum error = glGetError();
	if(error == GL_INVALID_VALUE){
		//log value
		return false;
	}

	m_buffer = 0;
	return true;
}

