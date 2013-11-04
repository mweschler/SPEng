#pragma once
#include <string>
#include "GLBuffer.h"

/*! An OpenGL shader for use in rendering
*/
class Shader
{
public:
	Shader();
	void setType(GLenum type);
	GLenum getType();
	bool compile();
	bool isCompiled();
	bool isLoaded();
	GLuint getID();
	virtual bool load(std::string filename);
	void loadFromString(std::string data);
	bool release();
	virtual ~Shader();
private:
	GLuint m_shader;
	GLenum m_type;
	bool m_compiled;
	std::string m_data;
	bool m_loaded;
};