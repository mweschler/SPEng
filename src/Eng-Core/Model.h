#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "GLBuffer.h"

class Model{
	
public:
	enum BufferType{
		VERTEX = 0,
		NORMAL = 1,
		INDEX = 2
	};

	Model();
	~Model();
	virtual bool load (std::string filename);
	bool load (std::vector<GLfloat> data);
	bool load (std::vector<GLfloat> verts, std::vector<GLushort> indicies);
	bool load (std::vector<GLfloat> verts, std::vector<GLfloat> normals, std::vector<GLushort> indicies);
	bool bind(BufferType) const;
	bool release();
	bool isLoaded() const;
	bool hasVerts() const;
	bool hasNormals() const;
	bool hasIndex() const;
	unsigned int getVertCount() const;
	unsigned int getIndexCount() const;
	void setVertCount(unsigned int count);
	void setIndexCount(unsigned int count);
	void setModelMatrix(glm::mat4 matrix);
	glm::mat4 getModelMatrix() const;
private:
	GLBuffer m_vertBuffer;
	GLBuffer m_normalBuffer;
	GLBuffer m_indexBuffer;
	bool m_dataLoaded;
	bool m_hasVerts;
	bool m_hasNormals;
	bool m_hasIndicies;
	unsigned int m_vertCount;
	unsigned int m_indexCount;
	glm::mat4 m_matrix;
};