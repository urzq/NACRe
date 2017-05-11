#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Transform.h"

Transform::Transform()
{
	m_Position = glm::vec3(0, 0, 0);
	m_Euler = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(1, 1, 1);
}

glm::vec3 Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

glm::vec3 Transform::GetEuler() const
{
	return m_Euler;
}

void Transform::SetEuler(const glm::vec3& euler)
{
	m_Euler = euler;
}

glm::vec3 Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 mat = glm::translate(glm::mat4(1.0f), m_Position);
	mat = mat * glm::eulerAngleYXZ(m_Euler.y, m_Euler.x, m_Euler.z);
	mat = glm::scale(mat, m_Scale);

	return mat;
}