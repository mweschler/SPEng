#include "Material.h"
#include "Logger.h"

Material::Material():
	m_diffuseColor(1.0f),
	m_program(NULL),
	m_texture(NULL)
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

void Material::setTexture(const Texture *texture){
	m_texture = texture;
}

bool Material::hasTexture() const{
	return (m_texture != NULL);
}

const Texture *Material::getTexture() const{
	return m_texture;
}
