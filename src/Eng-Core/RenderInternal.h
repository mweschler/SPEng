#pragma once

#include "glm\glm.hpp"
class Model;
class Material;
class Camera;

/*! Implements the rendering functionality for the rendering subystem */
class RenderInternal{
	
public:
	RenderInternal();
	/*! initializes the rendering system */
	bool initialize();
	/*! tells if the system has been initialized */
	bool isInitialized();
	/*! shuts down the system */
	void shutdown();
	/*! draws a model on the current context
		\param model the model to render
		\param material the material to render the model with
		\param camera the camera that is viewing the scene
	*/
	void drawModel(const Model model, const Material material, const Camera camera, glm::mat4 transform);
	/*! updates the system */
	void update();
	/*! sets the system into 3D mode
		\param fov the field of view to use
	*/
	void set3DMode(float fov);
	/*! sets the viewport for the current context
		\param x top left x position for the viewport
		\param y top left y position for the viewport
		\param width width of the viewport
		\param height height of the viewport
	*/
	void setViewPort(int x, int y, int width, int height);
	/*! sets the global light for the scene
		\param direction the direction of the global light
		\param color the color of the global light
	*/
	void setGlobalLight(glm::vec3 direction, glm::vec4 color);
	/*! sets the ambient lighting for the scene
		\param intensity the intensity of the ambient lighting
	*/
	void setAmbient(glm::vec4 intensity);
private:
	enum RenderMode {
		MODE_2D, 
		MODE_3D};
	bool m_initialized;
	glm::mat4 m_perspective;
	RenderMode m_renderMode;
	glm::vec3 m_lightDir;
	glm::vec4 m_lightColor;
	glm::vec4 m_ambient;
};