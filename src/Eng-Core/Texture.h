#pragma once
#include "Asset.h"
#include <string>
#include "SFML\Graphics\Texture.hpp"
#include "GL/glew.h"

/*! the size of a texture */
struct TextureSize{
	/*! the width of the texture */
	unsigned int width;
	/*! the height of the texture */
	unsigned int height;
};

/*! represents a texture used for rendering */
class Texture : public Asset{
public:
	Texture();
	/*! loads the texture from a file 
		/param filename the texture filename
		/return true on success
	*/
	virtual bool load(std::string filename);
	/*! releases the texture from memory*/
	void release();
	/*! binds the texture to the current context */
	bool bind() const;
	/*! gets the dimensions of the texture */
	TextureSize getSize() const;
	/*! sets texture smoothing on or off */
	void setSmoothing(bool);
	/*! tells if the texture is smoothed */
	bool isSmoothed() const;
	/*! set to repeate the texture */
	void setRepeated(bool);
	/*! tells if the texture is to be repreated */
	bool isRepeated() const;
private:
	GLuint m_texID;
	//sf::Texture *m_texture;
	
};