#pragma once
#include <glm/glm.hpp>

/*! Represents a camera in the game*/
class Camera{
public:
	Camera();
	/*! sets the position of the camera
		\param position the position of the camera
	*/
	void setPosition(glm::vec3 position);
	/*! gets the current position of the camera
		\return the position vector of the camera
	*/
	glm::vec3 getPosition() const;
	/*! sets the target point the camera looks at
		\param target position for the camera to look it
	*/
	void setTarget(glm::vec3 target);
	/*! gets the target position that the camera is looking at
		\return the position the camera is looking at
	*/
	glm::vec3 getTarget() const;
private:
	/*! position of the camera */
	glm::vec3 m_position;
	/*! target the camera is looking at */
	glm::vec3 m_target;
};