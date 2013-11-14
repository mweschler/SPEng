#include "Camera.h"

Camera::Camera():
	m_position(0.0f),
	m_target(10.0f)
{
}

void Camera::setPosition(glm::vec3 position){
	m_position = glm::vec3(position);
}

glm::vec3 Camera::getPosition() const{
	return m_position;
}

void Camera::setTarget(glm::vec3 target){
	m_target = glm::vec3(target);
}

glm::vec3 Camera::getTarget() const{
	return m_target;
}