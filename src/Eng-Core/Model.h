#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "GLBuffer.h"

/*! Representes a 3D model*/
class Model{
	
public:
	/*! the buffer types for a model */
	enum BufferType{
		VERTEX = 0,
		NORMAL = 1,
		INDEX = 2,
		TEXTURE = 3
	};

	Model();
	~Model();
	/*! loads the model from a file
		/param filename the file for the model
		/return true on success
	*/
	virtual bool load (std::string filename);
	/*! directly loads a model
		/param data vert data for the model
		/return true on success
	*/
	bool load (std::vector<GLfloat> data);
	/*! directly loads a model with indicies 
		/param verts the verticies of the model
		/param indicies the indicies for the model
		/return true on success
	*/
	bool load (std::vector<GLfloat> verts, std::vector<GLushort> indicies);
	/*! direcly loads a model with indicies and normals
		/param verts the vertices of the model
		/param normals the normals for the model
		/param indicies the indices for the model
		/return true on success
	*/
	bool load (std::vector<GLfloat> verts, std::vector<GLfloat> normals, std::vector<GLushort> indicies);
	/*! binds the model to the current context
		/param type the part of the model to bind
		/return true on success
	*/
	bool bind(BufferType type) const;
	/*! releases the model from the current context's memory
		/return true on success
	*/
	bool release();
	/*! tells if the model has been loaded 	*/
	bool isLoaded() const;
	/*! tells if the model has vertices */
	bool hasVerts() const;
	/*! tells if the model has normals */
	bool hasNormals() const;
	/*! tells if the model has indices */
	bool hasIndex() const;
	/*! tells if the model has texture coordinates */
	bool hasTexCords() const;
	/*! gets the total number of vertices */
	unsigned int getVertCount() const;
	/*! gets the total number of indices */
	unsigned int getIndexCount() const;
	/*! sets the total number of vertices 
		/param count the number of verties to set
	*/
	void setVertCount(unsigned int count);
	/*! sets the total number of indices
		/param count number of indices to set
	*/
	void setIndexCount(unsigned int count);
	/*! sets the model matrix
		/param matrix matrix to set
	*/
	void setModelMatrix(glm::mat4 matrix);
	/*! gets the model matrix */
	glm::mat4 getModelMatrix() const;
private:
	GLBuffer m_vertBuffer;
	GLBuffer m_normalBuffer;
	GLBuffer m_indexBuffer;
	GLBuffer m_texCordsBuffer;
	bool m_dataLoaded;
	bool m_hasVerts;
	bool m_hasNormals;
	bool m_hasIndicies;
	bool m_hasTexture;
	unsigned int m_vertCount;
	unsigned int m_indexCount;
	glm::mat4 m_matrix;
};