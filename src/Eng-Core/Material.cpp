#include "Material.h"
#include "Logger.h"

Material::Material():
	m_diffuseColor(1.0f),
	m_program(NULL),
	m_diffName(""),
	m_normAttrib(""),
	m_vertAttrib("")
{

}

bool Material::setShader(const ShaderProgram *program){
	if(program == NULL)
	{
		Logger &logger = *Logger::Instance();
		logger.writeToLog("Could not set material shader, program was NULL");
		return false;
	}

	if(!program->isLinked())
	{
		Logger &logger = *Logger::Instance();
		logger.writeToLog("Could not set material shader, program was not linked");
		return false;
	}

	m_program = program;

	return true;
}

void Material::setDiffuseColor(glm::vec3 color){
	m_diffuseColor = glm::vec3(color);
}

glm::vec3 Material::getDiffuseColor() const{
	return glm::vec3(m_diffuseColor);
}

const ShaderProgram *Material::getShader() const{
	return m_program;
}

void Material::setDiffuseName(std::string name){
	m_diffName = name;
}

std::string Material::getDiffuseName() const{
	return m_diffName;
}

void Material::setVertAtrib(std::string name){
	m_vertAttrib = name;
}

void Material::setNormAtrib(std::string name){
	m_normAttrib = name;
}

std::string Material::getVertAttrib() const{
	return m_vertAttrib;
}

std::string Material::getNormAttrib() const{
	return m_normAttrib;
}