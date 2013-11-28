#pragma once
#include "Asset.h"
#include <string>
#include "SFML\Graphics\Texture.hpp"

struct TextureSize{
	unsigned int width;
	unsigned int height;
};

class Texture : public Asset{
public:
	Texture();
	virtual bool load(std::string filename);
	void release();
	bool bind() const;
	TextureSize getSize() const;
	void setSmoothing(bool);
	bool isSmoothed() const;
	void setRepeated(bool);
	bool isRepeated() const;
private:
	sf::Texture *m_texture;
};