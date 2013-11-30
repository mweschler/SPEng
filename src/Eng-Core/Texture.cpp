#include "Texture.h"

Texture::Texture():
	m_texture(NULL)
{
}

bool Texture::load(std::string filename){
	m_texture = new sf::Texture();
	if(!m_texture->loadFromFile(filename))
		return false;

	return true;
}

void Texture::release(){
	delete m_texture;
	m_texture = NULL;
}

bool Texture::bind() const{
	if(m_texture == NULL)
		return false;

	m_texture->bind(m_texture);

	return true;
}

TextureSize Texture::getSize() const{
	sf::Vector2u size = m_texture->getSize();
	TextureSize tsize;
	tsize.width = size.x;
	tsize.height = size.y;

	return tsize;
}

void Texture::setSmoothing(bool value){
	m_texture->setSmooth(value);
}

bool Texture::isSmoothed() const{
	return m_texture->isSmooth();
}

void Texture::setRepeated(bool value){
	m_texture->setRepeated(value);
}

bool Texture::isRepeated() const{
	return m_texture->isRepeated();
}