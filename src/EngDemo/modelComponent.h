#include "IComponent.h"
#include "Model.h"
#include "Material.h"

class ModelComponent : public IComponent{
public:
	ModelComponent(Model *model, Material *material);
	virtual void update();
private:
	Model *m_model;
	Material *m_material;
};