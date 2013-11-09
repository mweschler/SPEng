#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"
#include "Logger.h"

static Logger *logger;
RenderInternal::RenderInternal():
	m_initialized(false)
{
	logger = Logger::Instance();

}

bool RenderInternal::initialize(){
	if(this->m_initialized == true)
		return false;
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	this->m_initialized = true;
	logger->writeToLog("Render System initialized");
	return true;
}

bool RenderInternal::isInitialized()
{
	return m_initialized;
}

void RenderInternal::shutdown(){
	this->m_initialized = false;
	logger->writeToLog("Render System Shutdown");
}

void RenderInternal::update(){
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderInternal::drawModel(const Model model, const Material material){
	const ShaderProgram &program = *material.getShader();
	if(model.hasVerts() && material.getVertAttrib().length() > 0)
	{
		model.bind(Model::VERTEX);
		GLuint vertLoc = glGetAttribLocation(program.getID(), material.getVertAttrib().c_str());
		glEnableVertexAttribArray(vertLoc);
		glVertexAttribPointer(vertLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
		return;

	if(model.hasNormals() && material.getNormAttrib().length() > 0){
		model.bind(Model::NORMAL);
		GLuint normLoc = glGetAttribLocation(program.getID(), material.getNormAttrib().c_str());
		glEnableVertexAttribArray(normLoc);
		glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if(material.getDiffuseName().length() > 0){
		GLuint diffLoc = glGetUniformLocation(program.getID(), material.getDiffuseName().c_str());
		glUniform3fv(diffLoc, 1, &(material.getDiffuseColor())[0]);
	}

	if(model.hasIndex())
	{
		model.bind(Model::INDEX);
		glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, 0);
	}
	else{
		glDrawArrays(GL_TRIANGLES, 0, model.getVertCount());
	}

	
}