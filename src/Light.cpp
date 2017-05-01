#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Light.h"
#include "shader/Program.h"

Light::Light(int matrixID):
	m_MatrixID(matrixID),
	m_TotalTime(0),
	m_Radius(2),
	m_Scale(0.7f)
{
}

void Light::Update(float dT)
{
	m_TotalTime += dT;

	float x = cos(m_TotalTime) * m_Radius;
	float y = sin(m_TotalTime) * m_Radius;
	float z = 5.0f;

	m_Position = glm::vec3(x, y, z);
}

void Light::Render(const glm::mat4& projection, const glm::mat4& view)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::scale(model, m_Scale);
	glm::mat4 MVP = projection * view * model;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 * 3 indices starting at 0 -> 12 triangles
}

glm::vec3 Light::GetPosition() const
{
	return m_Position;
}