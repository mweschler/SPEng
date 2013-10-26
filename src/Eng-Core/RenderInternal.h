#pragma once

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
private:
	bool m_initialized;
};