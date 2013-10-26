#pragma once

#include <GL/glew.h>

class GLBuffer{
	
public:
	GLBuffer(GLenum type);
	bool create();
	bool bind() const;
	bool release();
	GLenum getType() const;
private:
	GLBuffer();
	GLenum m_type;
	GLuint m_buffer;
};