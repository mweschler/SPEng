#pragma once

#include <GL/glew.h>
#include <string>

class GLHelper
{
public:
	static void flushGLErrors();
	static std::string errorEnumToString(GLenum error);
};