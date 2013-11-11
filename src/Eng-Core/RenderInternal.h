#pragma once

#include "glm\glm.hpp"
class Model;
class Material;
class Camera;

class RenderInternal{
	
public:
	RenderInternal();
	bool initialize();
	bool isInitialized();
	void shutdown();
	void drawModel(const Model model, const Material material, const Camera camera);
	void update();
	void set3DMode(float fov);
	void setViewPort(int x, int y, int width, int height);
private:
	enum RenderMode {
		MODE_2D, 
		MODE_3D};
	bool m_initialized;
	glm::mat4 m_perspective;
	RenderMode m_renderMode;
	
};