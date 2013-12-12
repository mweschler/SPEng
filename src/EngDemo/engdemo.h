#include "coregameapp.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "Texture.h"

class EngDemoApp: public CoreGameApp{
public:
	EngDemoApp();
protected:
	virtual bool initialize();
	virtual void update();
	virtual void render();
	virtual void shutdown();
private:
	Camera m_camera;
	Material m_material;
	ShaderProgram m_program;
	Model *m_model;
	Shader *m_vertShader;
	Shader *m_fragShader;
	Texture *m_texture;
};