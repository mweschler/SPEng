#pragma once
#include "glm\glm.hpp"

class Model;
class Material;
class Camera;

/*! intefrace for the rendering system */
class RenderManager {
public:
	/*! initializes the system */
	static bool initialize();
	/*! tells if the system is intialized */
	static bool isInitialized();
	/*! updates the system */
	static void update();
	/*! draws a model on the current context
		/param model the model to render
		/param material the material to render the model with
		/param camera the camera that is viewing the scene
	*/
	static void drawModel(const Model model,const Material material, const Camera camera, glm::mat4 transform = glm::mat4());
	/*! shuts down the system */
	static void shutdown();
	/*! sets the system into 3D mode
		/param fov the field of view to use
	*/
	static void set3DMode(float fov);
	/*! sets the viewport for the current context
		/param x top left x position for the viewport
		/param y top left y position for the viewport
		/param width width of the viewport
		/param height height of the viewport
	*/
	static void setViewport(int x, int y, int width, int height);
	/*! sets the global light for the scene
		/param direction the direction of the global light
		/param color the color of the global light
	*/
	static void setGlobalLight(glm::vec3 direction, glm::vec4 color);
	/*! sets the ambient lighting for the scene
		/param intensity the intensity of the ambient lighting
	*/
	static void setAmbient(glm::vec4 intensity);
};

