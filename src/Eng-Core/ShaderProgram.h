#pragma once

#include <GL/glew.h>
#include <string>

class Shader;

/*! Represents a shader program */
class ShaderProgram{
public:
	ShaderProgram();
	~ShaderProgram();
	/*! uses the program with the current context 
		\return true on success
	*/
	bool use() const;
	/*! linkes the shaders into a shader program 
		\param vertexShader vertex shader for this program
		\param fragmentShader fragment shader for this program
		\return true on success
	*/
	bool link(Shader &vertexShader, Shader &fragmentShader);
	/*! tells if the program is linked */
	bool isLinked() const;
	/*! releases the shader program from the context */
	bool release();
	/*! gets the OpenGL ID for this program */
	GLuint getID() const;
	/*! sets the name of the diffuse attribute for this program 
		\param name the name of the attribute
	*/
	void setDiffuseAttrib(std::string name);
	/*! gets the diffuse attribute name */
	std::string getDiffuseAttrib() const;
	/*! sets the name of the vertex attribute for this program
		\param the name of the attribute
	*/
	void setVertAttrib(std::string);
	/*! gets the name of the vertex attribute */
	std::string getVertAttrib() const;
	/*! sets the normal attribute name*/
	void setNormAttrib(std::string);
	/*! gets the normal attribute name */
	std::string getNormAttrib() const;
	/*! sets the Model View Perspective matrix attibute */
	void setMVPAttrib(std::string);
	/*! gets the MVP attrib */
	std::string getMVPAttrib() const;
	/*! sets the light direction and color attribute names */
	void setLightAttribs(std::string dir, std::string color);
	/*! gets the light direction attribute*/
	std::string getLightDirAttrib() const;
	/*! gets the light color attribute */
	std::string getLightColorAttrib() const;
	/*! sets the ambient lighting intensity attribute */
	void setAmbientAttrib(std::string);
	/*! gets the ambient lighting intesnsity attribute */
	std::string getAmbientAttrib() const;
	/*! sets the normal matrix attribute name*/
	void setNormMatrixAttrib(std::string);
	/*! gets the normal matrix attribute name */
	std::string getNormMatrixAttrib() const;
	/*! sets the uv texture coordiante attribute name */
	void setUVAttrib(std::string);
	/*! gets the uv texture coordinate attribute name */
	std::string getUVAttrib() const;
	/*! sets the sampler attribute name */
	void setSamplerAttrib(std::string);
	/*! gets the sampler attribute name */
	std::string getSamplerAttrib() const;
private:
	bool m_linked;
	GLuint m_program;
	std::string m_diffAttrib;
	std::string m_vertAttrib;
	std::string m_normAttrib;
	std::string m_MVPAttrib;
	std::string m_lightDir;
	std::string m_lightColor;
	std::string m_ambient;
	std::string m_normMatrix;
	std::string m_uvAttrib;
	std::string m_samplerAttrib;
};