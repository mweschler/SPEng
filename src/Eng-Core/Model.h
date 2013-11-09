#pragma once

#include <string>
#include <vector>
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
	bool bind(BufferType);
	bool release();
	bool isLoaded();
	bool hasVerts();
	bool hasNormals();
	bool hasIndex();

	
private:
	GLBuffer m_vertBuffer;
	GLBuffer m_normalBuffer;
	GLBuffer m_indexBuffer;
	bool m_dataLoaded;
	bool m_hasVerts;
	bool m_hasNormals;
	bool m_hasIndicies;
};