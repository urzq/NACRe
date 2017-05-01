#include <iostream>

#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

using namespace glm;

Camera::Camera(GLFWwindow* window):
	m_Window(window)
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

void Camera::Update(float dT)
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(m_Window, 1024/2, 768/2);

	// Compute new orientation
	m_HorizontalAngle += m_MouseSpeed * float(1024/2 - xpos );
	m_VerticalAngle   += m_MouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(m_HorizontalAngle - 3.14f/2.0f),
		0,
		cos(m_HorizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( m_Window, GLFW_KEY_UP ) == GLFW_PRESS){
		m_Position += direction * dT* m_Speed;
	}
	// Move backward
	if (glfwGetKey(m_Window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		m_Position -= direction * dT * m_Speed;
	}
	// Strafe right
	if (glfwGetKey(m_Window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		m_Position += right * dT * m_Speed;
	}
	// Strafe left
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		m_Position -= right * dT * m_Speed;
	}

	if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		std::cout << m_HorizontalAngle << " " << m_VerticalAngle <<  "\n";
		std::cout << m_Position.x << " " << m_Position.y << " " << m_Position.z << "\n";
	}

	float FoV = m_InitialFoV;

	m_ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + direction, up);
}