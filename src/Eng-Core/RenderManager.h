#pragma once
#include "glm\glm.hpp"

class Model;
class Material;
class Camera;

class RenderManager {
public:
	static bool initialize();
	static bool isInitialized();
	static void update();
	static void drawModel(const Model model,const Material material, const Camera camera);
	static void shutdown();
	static void set3DMode(float fov);
	static void setViewport(int x, int y, int width, int height);
	static void setGlobalLight(glm::vec3 direction, glm::vec4 color);
	static void setAmbient(glm::vec4 intensity);
};

