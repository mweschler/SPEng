#include <sstream>
#include "RenderInternal.h"
#include "Model.h"
#include "Material.h"
#include "Logger.h"
#include "glm/ext.hpp"
#include "GLHelper.h"
#include "Camera.h"
#include "ConfigurationManager.h"

static Logger *logger;
RenderInternal::RenderInternal():
	m_initialized(false),
	m_perspective(),
	m_renderMode(RenderInternal::MODE_2D),
	m_lightDir(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_lightColor(1.0f),
	m_ambient(0.3f)
{
	logger = Logger::Instance();
}

bool RenderInternal::initialize(){
	if(this->m_initialized == true)
		return false;
	//set default resolution
	
	ConfigurationManager &config = *ConfigurationManager::Instance();
	config.setVariable<int> ("w_width", 800);
	config.setVariable<int> ("w_height", 600);
	config.setVariable<bool> ("w_fullscreen", false);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderInternal::drawModel(const Model model, const Material material, const Camera camera, glm::mat4 transform){
	const ShaderProgram &program = *material.getShader();
	program.use();

	//setup verts
	if(model.hasVerts() && program.getVertAttrib().length() > 0)
	{
		model.bind(Model::VERTEX);
		GLuint vertLoc = glGetAttribLocation(program.getID(), program.getVertAttrib().c_str());
		glEnableVertexAttribArray(vertLoc);
		glVertexAttribPointer(vertLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
		return; //no verts? nothing to render

	//setup normals
	if(model.hasNormals() && program.getNormAttrib().length() > 0){
		model.bind(Model::NORMAL);
		GLint normLoc = glGetAttribLocation(program.getID(), program.getNormAttrib().c_str());
		glEnableVertexAttribArray(normLoc);
		glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	//set global diffuse
	if(program.getDiffuseAttrib().length() > 0){
		GLint diffLoc = glGetUniformLocation(program.getID(), program.getDiffuseAttrib().c_str());
		glUniform3fv(diffLoc, 1, glm::value_ptr(material.getDiffuseColor()));
	}

	glm::mat4 view = glm::lookAt(camera.getPosition(), camera.getTarget(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mv =   view  *  transform * model.getModelMatrix();

	//set MVP matrix
	if(program.getMVPAttrib().length() > 0){
		GLint mvpLoc = glGetUniformLocation(program.getID(), program.getMVPAttrib().c_str());
		glm::mat4 mvp = m_perspective * mv;
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	//setup normal matrix
	if(program.getNormMatrixAttrib().length() > 0){
		GLint normMatLoc = glGetUniformLocation(program.getID(), program.getNormMatrixAttrib().c_str());
		
		glm::mat3 normMat = glm::mat3(glm::transpose(glm::inverse(mv)));
		glUniformMatrix3fv(normMatLoc, 1, GL_FALSE, glm::value_ptr(normMat));
	}

	//setup global lighting
	if(program.getLightDirAttrib().length() > 0 && program.getLightColorAttrib().length() > 0){
		GLint lightDirLoc = glGetUniformLocation(program.getID(), program.getLightDirAttrib().c_str());
		glm::vec3 dir = glm::normalize(glm::mat3(mv) * m_lightDir);
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(dir));

		GLint lightColorLoc = glGetUniformLocation(program.getID(), program.getLightColorAttrib().c_str());
		glUniform4fv(lightColorLoc, 1, glm::value_ptr(m_lightColor));
	}

	//set ambient intensity
	if(program.getAmbientAttrib().length() > 0){
		GLint ambLoc = glGetUniformLocation(program.getID(), program.getAmbientAttrib().c_str());
		glUniform4fv(ambLoc, 1, glm::value_ptr(m_ambient));
	}

	//use texture sampler
	if(program.getSamplerAttrib().length() > 0 && material.hasTexture()){
		GLint samplerLoc = glGetUniformLocation(program.getID(), program.getSamplerAttrib().c_str());
		glActiveTexture(GL_TEXTURE0);
		material.getTexture()->bind();
		glUniform1i(samplerLoc, 0);
	}

	//use texcords
	if(program.getUVAttrib().length() > 0 && model.hasTexCords()){
		GLint uvLoc = glGetAttribLocation(program.getID(), program.getUVAttrib().c_str());
		model.bind(Model::TEXTURE);
		glEnableVertexAttribArray(uvLoc);
		glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	//draw in indexed or array mode
	if(model.hasIndex())
	{
		model.bind(Model::INDEX);
		glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, 0);
	}
	else{
		glDrawArrays(GL_TRIANGLES, 0, model.getVertCount());
	}

	
}

void RenderInternal::set3DMode(float fov){
	m_renderMode = RenderMode::MODE_3D;
	int viewport[4];
	GLHelper::flushGLErrors();
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLenum rv = glGetError();
	if(rv != GL_NO_ERROR){
		Logger &logger = *Logger::Instance();
		std::stringstream ss;
		ss<<"RenderManager: failed to get viewport, error ";
		ss<<GLHelper::errorEnumToString(rv);
		logger.writeToLog(ss.str());
		return;
	}

	float ratio = static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]);

	m_perspective = glm::perspective(fov, ratio, 1.0f, 1000.0f);
}

void RenderInternal::setViewPort(int x, int y, int width, int height){
	if(x < 0 || y < 0 || width <0 || height < 0){
		Logger &logger = *Logger::Instance();

		logger.writeToLog("Render Manager: failed to set viewport, invalid value");
		return;
	}

	GLHelper::flushGLErrors();

	glViewport(x, y, width, height);
	GLenum rv = glGetError();
	if(rv != GL_NO_ERROR){
		Logger &logger = *Logger::Instance();
		std::stringstream ss;
		ss<<"Call to glViewport failed, error ";
		ss<<GLHelper::errorEnumToString(rv);
		logger.writeToLog(ss.str());
	}
}

void RenderInternal::setGlobalLight(glm::vec3 direction, glm::vec4 color){
	m_lightDir = direction;
	m_lightColor = color;
}

void RenderInternal::setAmbient(glm::vec4 intensity){
	m_ambient = intensity;
}