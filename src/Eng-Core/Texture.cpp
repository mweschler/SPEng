#include "Texture.h"
#include "GL\glew.h"
#include "GLHelper.h"
#include <sstream>
#include <iostream>

Texture::Texture():
	//m_texture(NULL),
	m_texID(0)
{
}

bool Texture::load(std::string filename){
	//m_texture = new sf::Texture();
	sf::Image img;
	if(!img.loadFromFile(filename))
		return false;
	//if(!m_texture->loadFromFile(filename))
	//	return false;

	sf::Vector2u size = img.getSize();

	unsigned int tex = 0;
	GLHelper::flushGLErrors();

	glGenTextures (1, &tex);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load, gen textures: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}

	glActiveTexture (GL_TEXTURE0);

	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load, active texture: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}

	glBindTexture (GL_TEXTURE_2D, tex);

	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load, bind texture: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}

	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  size.x ,
	  size.y ,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  img.getPixelsPtr()
	);

	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load, teximage2d: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "Error in texture load: "<< GLHelper::errorEnumToString(error);
		std::cout<<ss.str()<<std::endl;

		return false;
	}

	this->m_texID = tex;
	return true;
}

void Texture::release(){
	//delete m_texture;
	//m_texture = NULL;
}

bool Texture::bind() const{
	//if(m_texture == NULL)
	//	return false;

	/*m_texture->bind(m_texture);*/

	glBindTexture(GL_TEXTURE_2D, m_texID);

	return true;
}

TextureSize Texture::getSize() const{
	
	TextureSize tsize;
	tsize.width = 0;
	tsize.height = 0;

	return tsize;
}

void Texture::setSmoothing(bool value){
	//m_texture->setSmooth(value);
}

bool Texture::isSmoothed() const{
	return false;
}

void Texture::setRepeated(bool value){
	//m_texture->setRepeated(value);
}

bool Texture::isRepeated() const{
	return false;
}