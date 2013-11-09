#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <string>



class Material{
public:
	Material();
	bool setShader(const ShaderProgram *program);
	void setDiffuseColor(glm::vec3);
	const ShaderProgram *getShader() const;
	glm::vec3 getDiffuseColor() const;
	void setDiffuseName(std::string name);
	std::string getDiffuseName() const;
	void setVertAtrib(std::string);
	std::string getVertAttrib() const;
	void setNormAtrib(std::string);
	std::string getNormAttrib() const;
private:
	glm::vec3 m_diffuseColor;
	const ShaderProgram *m_program;
	std::string m_diffName;
	std::string m_vertAttrib;
	std::string m_normAttrib;
};