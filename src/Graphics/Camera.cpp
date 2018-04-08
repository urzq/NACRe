#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

#include "Input/InputManager.h"

using namespace glm;

Camera::Camera()
{
	m_IsEnabled = true;
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

void Camera::SetEnabled(bool enabled)
{
	m_IsEnabled = enabled;
}

void Camera::Update(float dT)
{
	if (!m_IsEnabled)
	{
		return;
	}

	// TODO: abstract those call in InputManager.
	GLFWwindow* window = ServiceLocator::Get<Renderer>()->GetGLFWwindow();

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// TODO: get the actual window size.

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
	
	glm::vec3 up = glm::cross( right, direction );

	auto inputManager = ServiceLocator::Get<InputManager>();

	// Move forward
	if (inputManager->IsKeyDown(GLFW_KEY_UP)){
		m_Position += direction * dT* m_Speed;
	}
	// Move backward
	if (inputManager->IsKeyDown(GLFW_KEY_DOWN)) {
		m_Position -= direction * dT * m_Speed;
	}
	// Strafe right
	if (inputManager->IsKeyDown(GLFW_KEY_RIGHT)) {
		m_Position += right * dT * m_Speed;
	}
	// Strafe left
	if (inputManager->IsKeyDown(GLFW_KEY_LEFT)) {
		m_Position -= right * dT * m_Speed;
	}

	float FoV = m_InitialFoV;

	m_ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + direction, up);
}