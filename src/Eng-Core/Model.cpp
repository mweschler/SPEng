#include "Model.h"
#include "GLHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model():
	m_vertBuffer(GL_ARRAY_BUFFER),
	m_normalBuffer(GL_ARRAY_BUFFER),
	m_indexBuffer(GL_ELEMENT_ARRAY_BUFFER),
	m_dataLoaded(false),
	m_hasVerts(false),
	m_hasNormals(false),
	m_hasIndicies(false),
	m_vertCount(0),
	m_indexCount(0),
	m_matrix(1.0f)
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

	glBufferData(buffer.getType(), sizeof(T) * data.size(), &data[0], GL_STATIC_DRAW);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR){
		std::cout<<"Error binding data "<<GLHelper::errorEnumToString(error)<<std::endl;
		buffer.release();
		return false;
	}

	return true;
}

void parseStringPart(std::string data,GLshort &vertexIndex, GLshort &normalIndex){
	//find vertex index section
	int position = data.find("/");
	if(position = std::string::npos){
		std::istringstream vertstream(data);
		vertstream >> vertexIndex;
		normalIndex = 0;
		return;
	} else {
		std::istringstream vertstream(data.substr(0,position));
		vertstream >> vertexIndex;

		position = data.find("/", position);
		//ignore texture index

		//rest is normal index;
		position = data.find("/", position);
		std::istringstream normstream(data.substr(position + 1));
		normstream >> normalIndex;
	}
}

void calculateNormals(std::vector<glm::vec4> verticies, std::vector<glm::vec3> &normals, std::vector<GLushort> elements)
	{
		//initialize the normals withe one for every vertex
		normals.resize(verticies.size(), glm::vec3(0.0, 0.0, 0.0));

		//iterate through each face and calculate normals
		for(int i = 0; i < elements.size(); i+=3){
			glm::vec3 vert1 = glm::vec3(verticies[elements[i]]);
			glm::vec3 vert2 = glm::vec3(verticies[elements[i + 1]]);
			glm::vec3 vert3 = glm::vec3(verticies[elements[i + 2]]);

			//calculate normal for this face
			glm::vec3 normal = glm::normalize(glm::cross(vert3 - vert1, vert2 - vert1));	
			//apply normal for each vert index;
			
		}
	}

bool Model::load(std::string filename){
	if(isLoaded())
		return false;
	std::ifstream file;
	file.open(filename, std::ios::in);

	if(!file.is_open()){
		std::cout<<"Could not open OBJ file "<<filename<<std::endl;
		return NULL;
	}

	std::vector<glm::vec4> verticies; 
	std::vector<GLushort> elements;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> normalTemp;
	std::vector<GLushort> normalIndexs;
	bool normalsIncluded = false;

	//parse file
	std::string line;
	while(std::getline(file, line)){
		if(line.substr(0,2) == "v "){
			//found a verticies
			std::istringstream stream(line.substr(2));
			glm::vec4 vertex;
			stream >> vertex.x;
			stream >> vertex.y;
			stream >> vertex.z;
			vertex.w = 1.0f;

			verticies.push_back(vertex);
		} else if(line.substr(0,3) == "vn "){
			normalsIncluded = true;
			std::istringstream stream(line.substr(3));
			glm::vec3 normal;
			stream >> normal.x;
			stream >> normal.y;
			stream >> normal.z;

			normalTemp.push_back(normal);
		} else if (line.substr(0,2) == "f "){
			//found a face

			GLshort vert1, vert2, vert3, norm1, norm2, norm3;
			int position = line.find(" ", 3);
			std::string sub = line.substr(2, position - 1);
			parseStringPart(sub, vert1, norm1);
			int nextSpace = line.find(" ", position + 1);

			parseStringPart(line.substr(position + 1, nextSpace - position - 1), vert2, norm2);
			parseStringPart(line.substr(nextSpace + 1), vert3, norm3);

			//offset indicies to start at 0, not 1
			vert1--;
			vert2--;
			vert3--;
			norm1--;
			norm2--;
			norm3--;
			if(norm1 >0)
				normalsIncluded = true;

			elements.push_back(vert1);
			elements.push_back(vert2);
			elements.push_back(vert3);
			normalIndexs.push_back(norm1);
			normalIndexs.push_back(norm2);
			normalIndexs.push_back(norm3);
		} else { 
			//Only verticies and faces will be processed
		}
	}

	file.close();
	if(!normalsIncluded)
		calculateNormals(verticies, normals, elements);

	if(!loadBuffer(m_vertBuffer, verticies))
		return false;

	m_hasVerts = true;
	m_vertCount = verticies.size() * 4;

	
	if(!loadBuffer(m_indexBuffer, elements))
		return false;

	m_hasIndicies = true;
	m_indexCount = elements.size();

	if(!loadBuffer(m_normalBuffer, normals))
		return false;

	m_hasNormals = true;

	m_dataLoaded = true;

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

bool Model::bind(BufferType type) const{
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

bool Model::isLoaded() const{
	return m_dataLoaded;
}

bool Model::hasVerts() const{
	return m_hasVerts;
}

bool Model::hasNormals() const{
	return m_hasNormals;
}

bool Model::hasIndex() const{
	return m_hasIndicies;
}

unsigned int Model::getVertCount() const{
	return m_vertCount;
}

unsigned int Model::getIndexCount() const{
	return m_indexCount;
}

void Model::setVertCount(unsigned int count){
	m_vertCount = count;
}

void Model::setIndexCount(unsigned int count){
	m_indexCount = count;
}

void Model::setModelMatrix(glm::mat4 matrix){
	m_matrix = matrix;
}

glm::mat4 Model::getModelMatrix() const{
	return m_matrix;
}