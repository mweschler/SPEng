#pragma once

#include <GL/glew.h>
#include <string>

class Shader;

class ShaderProgram{
public:
	ShaderProgram();
	~ShaderProgram();
	bool use() const;
	bool link(Shader &vertexShader, Shader &fragmentShader);
	bool isLinked() const;
	bool release();
	GLuint getID() const;
	void setDiffuseAttrib(std::string name);
	std::string getDiffuseAttrib() const;
	void setVertAttrib(std::string);
	std::string getVertAttrib() const;
	void setNormAttrib(std::string);
	std::string getNormAttrib() const;
	void setMVPAttrib(std::string);
	std::string getMVPAttrib() const;
	void setLightAttribs(std::string dir, std::string color);
	std::string getLightDirAttrib() const;
	std::string getLightColorAttrib() const;
	void setAmbientAttrib(std::string);
	std::string getAmbientAttrib() const;
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
};