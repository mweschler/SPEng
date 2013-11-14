#pragma once

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
};

