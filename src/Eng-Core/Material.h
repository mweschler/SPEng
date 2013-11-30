#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <string>



class Material{
public:
	Material();
	bool setShader(const ShaderProgram *program);
	void setDiffuseColor(glm::vec3);
	const ShaderProgram *getShader() const;
	glm::vec3 getDiffuseColor() const;
	void setTexture(const Texture *texture);
	bool hasTexture() const;
	const Texture *getTexture() const;
private:
	glm::vec3 m_diffuseColor;
	const ShaderProgram *m_program;
	const Texture *m_texture;
};