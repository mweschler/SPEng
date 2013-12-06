#pragma once
#include <string>
#include "GLBuffer.h"
#include "Asset.h"

/*! An OpenGL shader for use in rendering
*/
class Shader : public Asset
{
public:
	/*! Initializes a shader object ready for data */
	Shader();
	/*! Sets the type of shader for this object
		\param type Eiter GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	*/
	void setType(GLenum type);
	/*! Gets the type for this shader
		\return the current type of GL Shader
	*/
	GLenum getType();
	/*! Compiles the shader for use in a shader program
		\return true on success, false otherwise
	*/
	bool compile();
	/*! Gets the compilation status
		\return ture if compiled, false otherwise
	*/
	bool isCompiled();
	/*! Tells if the data has been loaded or not
		\return ture if loaded, false otherwise
	*/
	bool isLoaded();
	/*! Gets the OpenGL ID for this shader
		\return the ID of the shader
	*/
	GLuint getID();
	/*! Loads the shader data from a file
		\param filename The location and name of the file to load
		\return ture if succesfully loaded into local memory
	*/
	virtual bool load(std::string filename);
	/*! loads the shader from a string 
		/param data string containg the data
	*/
	void loadFromString(std::string data);
	/*! Releases the shader from OpenGL
		\return true if the shader was released from memory
	*/
	bool release();

	virtual ~Shader();
private:
	GLuint m_shader;
	GLenum m_type;
	bool m_compiled;
	std::string m_data;
	bool m_loaded;
};