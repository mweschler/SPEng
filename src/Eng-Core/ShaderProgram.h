#pragma once

#include <GL/glew.h>

class Shader;

class ShaderProgram{
public:
	ShaderProgram();
	~ShaderProgram();
	bool use() const;
	bool link(Shader &vertexShader, Shader &fragmentShader);
	bool isLinked() const;
	bool release();
private:
	bool m_linked;
	GLuint m_program;
};