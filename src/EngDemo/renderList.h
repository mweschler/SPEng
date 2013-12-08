#include <stdlib.h>
#include <vector>
#include <Material.h>
#include <Model.h>
#include <Camera.h>

struct RenderObject{
	Model *model;
	Material *material;
};

class RenderList{
public:
	static RenderList *Instance();
	RenderList();
	void update();
	void renderList(Camera camera);
	void add(Model *model, Material *material);
private:
	std::vector<RenderObject> m_objects;
};