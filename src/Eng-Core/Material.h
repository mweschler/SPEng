#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>



class Material{
public:
	Material();
	bool setShader(const ShaderProgram *program);
	void setDiffuseColor(glm::vec3);
	const ShaderProgram *getShader() const;
	glm::vec3 getDiffuseColor() const;
private:
	glm::vec3 m_diffuseColor;
	const ShaderProgram *m_program;
};