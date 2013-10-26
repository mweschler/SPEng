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
};

