#include "IComponent.h"
#include "Model.h"
#include "Material.h"

class ModelComponent : public IComponent{
public:
	ModelComponent(Model *model, Material *material);
	void setRotation(glm::vec3 rotation);
	virtual void update();
private:
	Model *m_model;
	Material *m_material;
	glm::mat4 m_rotation;
};