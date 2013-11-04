#pragma once

#include <GL/glew.h>


class Shader;

class ShaderProgram{
public:
	ShaderProgram();
	~ShaderProgram();
	bool use();
	bool link(Shader &vertexShader, Shader &fragmentShader);
	bool isLinked();
	bool release();
private:
	bool m_linked;
	GLuint m_program;
};