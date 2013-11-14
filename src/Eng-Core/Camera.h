#pragma once
#include <glm/glm.hpp>

class Camera{
public:
	Camera();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;
	void setTarget(glm::vec3 target);
	glm::vec3 getTarget() const;
private:
	glm::vec3 m_position;
	glm::vec3 m_target;
};