#pragma once

#include <GL/glew.h>

/*! Represents an OpenGL buffer */
class GLBuffer{
	
public:
	/*! Represents an OpenGL buffer
		\param type The type of buffer this object represents
	*/
	GLBuffer(GLenum type);

	/*! Creates the buffer in the current context
		\return true if succesful
	*/
	bool create();
	/*! Binds the buffer to the current context
		\return true if succesfully bound
	*/
	bool bind() const;
	/*! Releases the buffer from the current context
		\return true on success
	*/
	bool release();
	/*! Gets the GLBuffer type
		\return buffer type
	*/
	GLenum getType() const;
private:
	GLBuffer();

	/*! the type of buffer this represents */
	GLenum m_type;
	/*! the buffer id */
	GLuint m_buffer;
};