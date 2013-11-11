#pragma once

class Model;
class Material;

class RenderManager {
public:
	static bool initialize();
	static bool isInitialized();
	static void update();
	static void drawModel(const Model model,const Material material);
	static void shutdown();
	static void set3DMode(float fov);
	static void setViewport(int x, int y, int width, int height);
};

