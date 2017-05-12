#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	void Update(float dT);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition() const;

private:
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	
	glm::vec3 m_Position = glm::vec3(3.24f, 0.66f, 5.57f);

	float m_HorizontalAngle = 3.66f;
	float m_VerticalAngle = -0.11f;
	float m_InitialFoV = 45.0f;

	float m_Speed = 3.0f; // 3 units / second
	float m_MouseSpeed = 0.005f;
};

#endif