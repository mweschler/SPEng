#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <string>


/*! Represents a material that defines how something should be rendered */
class Material{
public:
	Material();
	/*! sets the shader program to be used as part of this material
		\param program the shader program to use
		\return true on success
	*/
	bool setShader(const ShaderProgram *program);
	/*! sets the diffuse color to use
		\param color the diffuse color to use
	*/
	void setDiffuseColor(glm::vec3 color);
	/*! gets the shader program in use by the material
		\return the shader program
	*/
	const ShaderProgram *getShader() const;
	/*! gets the diffuse color in use
		\return the diffuse color
	*/
	glm::vec3 getDiffuseColor() const;
	/*! sets the texture to for the material
		\param texture the texture for this material to use
	*/
	void setTexture(const Texture *texture);
	/*! tells if the material has a texture
		\return true if there is a texture associated with the material
	*/
	bool hasTexture() const;
	/*! gets the texture used by the material
		\return a texture used by the material
	*/
	const Texture *getTexture() const;
private:
	/*! diffuse color */
	glm::vec3 m_diffuseColor;
	/*! shader program */
	const ShaderProgram *m_program;
	/*! texture */
	const Texture *m_texture;
};