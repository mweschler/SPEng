#include "coregameapp.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "Texture.h"
#include "modelComponent.h"
#include <vector>
#include "AudioContainer.h"

class EngDemoApp: public CoreGameApp{
public:
	EngDemoApp();
protected:
	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void shutdown();
	double checkPointDistance(sf::Vector2i);
	int findObjectIndex(ModelComponent *object);
	void rotateObjects(std::vector<ModelComponent *> objects);
private:
	Camera m_camera;
	AudioContainer* clickSound;
	Material m_material;
	ShaderProgram m_program;
	Model *m_model;
	Model *m_quad;
	Shader *m_vertShader;
	Shader *m_fragShader;
	Texture *m_texture;
	Texture *m_backdrop;
	std::vector<ModelComponent *> m_components;
	std::vector<ModelComponent *> m_rotating;
};