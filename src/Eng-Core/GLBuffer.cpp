#include <GL/glew.h>
#include "GLBuffer.h"
#include "assertions.h"
#include "GLHelper.h"

#include <iostream>

/*! Represents an OpenGL buffer
	\param type The type of buffer this object represents
*/
GLBuffer::GLBuffer(GLenum type):
	m_type(type),
	m_buffer(0)
{
}

GLBuffer::GLBuffer(){
	ASSERT(false); //should never get here
}


/*! Binds the buffer to the current context
	\return true if succesfully bound
*/
bool GLBuffer::bind() const{
	if(m_buffer == 0){
		return false;
	}
	
	GLHelper::flushGLErrors();

	glBindBuffer(m_type, m_buffer);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::cout<<"Error binding buffer "<<GLHelper::errorEnumToString(error)<<std::endl;
		return false;
	}

	return true;
}

/*! Creates the buffer in the current context
	\return true if succesful
*/
bool GLBuffer::create(){
	GLHelper::flushGLErrors();

	if(m_buffer != 0  || glIsBuffer(m_buffer) == GL_TRUE){
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

/*! Gets the GLBuffer type
	\return buffer type
*/
GLenum GLBuffer::getType() const{
	return this->m_type;
}

/*! Releases the buffer from the current context
	\return true on success
*/
bool GLBuffer::release(){
	if(m_buffer == 0){
		//log error
		return false;
	}

	GLHelper::flushGLErrors();

	glDeleteBuffers(1, &m_buffer);
	GLenum error = glGetError();
	if(error == GL_INVALID_VALUE){
		//log value
		return false;
	}

	m_buffer = 0;
	return true;
}

