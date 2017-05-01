#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(GLFWwindow* window);

	void Update(float dT);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition() const;

private:
	GLFWwindow* m_Window;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	// Initial position : on +Z
	glm::vec3 m_Position = glm::vec3(3.83f, 0.82f, 6.85f);

	// Initial horizontal angle : toward -Z
	float m_HorizontalAngle = 3.8f;
	// Initial vertical angle : none
	float m_VerticalAngle = -0.11;
	// Initial Field of View
	float m_InitialFoV = 45.0f;

	float m_Speed = 3.0f; // 3 units / second
	float m_MouseSpeed = 0.005f;
};

#endif