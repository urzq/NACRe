#include <iostream>

#include <GL/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

using namespace glm;

Camera::Camera()
{
}

glm::mat4 Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}


void Camera::Update(float dT)
{
	GLFWwindow* window = ServiceLocator::GetInstance()->GetRenderer()->GetGLFWwindow();

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

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
	if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
		m_Position += direction * dT* m_Speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		m_Position -= direction * dT * m_Speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		m_Position += right * dT * m_Speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		m_Position -= right * dT * m_Speed;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		std::cout << m_HorizontalAngle << " " << m_VerticalAngle <<  "\n";
		std::cout << m_Position.x << " " << m_Position.y << " " << m_Position.z << "\n";
	}

	float FoV = m_InitialFoV;

	m_ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + direction, up);
}