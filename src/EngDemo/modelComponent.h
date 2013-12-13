#pragma once
#include "IComponent.h"
#include "Model.h"
#include "Material.h"

class ModelComponent : public IComponent{
public:
	ModelComponent(Model *model, Material *material);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation() const;
	virtual void update();
private:
	Model *m_model;
	Material *m_material;
	glm::vec3 m_lastRotate;
	glm::mat4 m_rotation;
};