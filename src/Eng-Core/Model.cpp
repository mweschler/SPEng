#include "Model.h"
#include "GLHelper.h"
#include <iostream>

Model::Model():
	m_vertBuffer(GL_ARRAY_BUFFER),
	m_normalBuffer(GL_ARRAY_BUFFER),
	m_indexBuffer(GL_ELEMENT_ARRAY_BUFFER),
	m_dataLoaded(false),
	m_hasVerts(false),
	m_hasNormals(false),
	m_hasIndicies(false)
{

}

Model::~Model(){

}

template <typename T>
static bool loadBuffer(GLBuffer &buffer, std::vector<T> data){
	if(!buffer.create())
	{
		std::cout<<"Failed to create buffe"<<std::endl;
		return false;
	}
	if(!buffer.bind()){
		std::cout<<"Failed to bind buffer"<<std::endl;
		buffer.release();
		return false;
	}

	glGetError(); //clear any uncaught errors. Report this?
	if(buffer.getType() != GL_ARRAY_BUFFER)
		std::cout<<"Not array buffer"<<std::endl;

	glBufferData(buffer.getType(), sizeof(T) * data.size(), &data[0], GL_STATIC_DRAW);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::cout<<"Error binding data "<<GLHelper::errorEnumToString(error)<<std::endl;
		buffer.release();
		return false;
	}

	return true;
}


bool Model::load(std::string filename){
	if(isLoaded())
		return false;
	//NYI
	return true;
}

bool Model::load(std::vector<GLfloat> verts){
	if(isLoaded())
	{
		std::cout<<"Already loaded"<<std::endl;
		return false;
	}

	if(!loadBuffer(m_vertBuffer, verts))
	{
		std::cout<<"Failed to load buffer"<<std::endl;
		return false;
	}

	m_hasVerts = true;
	m_dataLoaded = true;
	return true;
}

bool Model::load(std::vector<GLfloat> verts, std::vector<GLushort> indicies){
	if(isLoaded())
	{
		
		return false;
	}

	if(!loadBuffer(m_vertBuffer, verts))
		return false;	
	
	if(!loadBuffer(m_indexBuffer, indicies)){
		m_vertBuffer.release();
		return false;
	}

	m_hasVerts = true;
	m_hasIndicies = true;
	m_dataLoaded = true;
	return true;
}

bool Model::load(std::vector<GLfloat> verts, std::vector<GLfloat> normals, std::vector<GLushort> indicies){
	if(isLoaded())
		return false;

	if((verts.size() / 4) != (normals.size() / 3))
		return false;

	if(!loadBuffer(m_vertBuffer, verts))
		return false;

	if(!loadBuffer(m_normalBuffer, normals)){
		m_vertBuffer.release();
		return false;
	}

	if(!loadBuffer(m_indexBuffer, indicies)){
		m_normalBuffer.release();
		m_vertBuffer.release();
		return false;
	}

	m_hasVerts = true;
	m_hasNormals = true;
	m_hasIndicies = true;
	m_dataLoaded = true;
	return true;
}

bool Model::bind(BufferType type){
	if(type == Model::VERTEX && m_hasVerts)
		return m_vertBuffer.bind();
	if(type == Model::NORMAL && m_hasNormals)
		return m_normalBuffer.bind();
	if(type == Model::INDEX && m_hasIndicies)
		return m_indexBuffer.bind();

	return false;
}

bool Model::release(){
	if(m_dataLoaded == false)
		return false;

	if(m_hasVerts && !m_vertBuffer.release())
		return false;

	m_hasVerts = false;

	if(m_hasNormals && !m_normalBuffer.release())
		return false;

	m_hasNormals = false;

	if(m_hasIndicies && !m_indexBuffer.release())
		return false;

	m_hasIndicies = false;

	m_dataLoaded = false;
	return true;
}

bool Model::isLoaded(){
	return m_dataLoaded;
}

bool Model::hasVerts(){
	return m_hasVerts;
}

bool Model::hasNormals(){
	return m_hasNormals;
}

bool Model::hasIndex(){
	return m_hasIndicies;
}

