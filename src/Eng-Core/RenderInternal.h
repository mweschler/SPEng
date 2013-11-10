#pragma once

#include "glm\glm.hpp"
class Model;
class Material;

class RenderInternal{
public:
	RenderInternal();
	bool initialize();
	bool isInitialized();
	void shutdown();
	void drawModel(const Model model, const Material material);
	void update();
	void set3DMode(float fov);
private:
	bool m_initialized;
	glm::mat4 m_perspective;
};