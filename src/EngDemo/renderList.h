#include <stdlib.h>
#include <vector>
#include <Material.h>
#include <Model.h>
#include <Camera.h>

struct RenderObject{
	Model *model;
	Material *material;
	glm::mat4 transform;
};

class RenderList{
public:
	static RenderList *Instance();
	RenderList();
	void update();
	void renderList(Camera camera);
	void add(Model *model, Material *material, glm::mat4 transform = glm::mat4());
private:
	std::vector<RenderObject> m_objects;
};