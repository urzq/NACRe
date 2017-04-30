#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
#include "shader/Program.h"

Cube::Cube(const Program& program, float initTime):
	m_TotalTime(initTime)
{
	m_Position = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(0.7f);

	m_ObjectColor	= program.GetUniformLocation("objectColor");
	m_LightColor	= program.GetUniformLocation("lightColor");
	m_LightPos		= program.GetUniformLocation("lightPos");
	m_Model			= program.GetUniformLocation("model");
	m_View			= program.GetUniformLocation("view");
	m_Proj			= program.GetUniformLocation("projection");
}

void Cube::SetPosition(glm::vec3& position)
{
	m_Position = position;
}

void Cube::Update(float dT)
{
	m_TotalTime += dT;
	m_OffsetPosition.z = sin(m_TotalTime);
}

void Cube::Render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& lightPos)
{
	glUniform3f(m_ObjectColor, 1.0f, 0.5f, 0.31f);
	glUniform3f(m_LightColor, 1.0f, 1.0f, 1.0f);
	glUniform3f(m_LightPos, lightPos.x, lightPos.y, lightPos.z);

	// Pass the matrices to the shader
	glUniformMatrix4fv(m_View, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(m_Proj, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(m_Model, 1, GL_FALSE, glm::value_ptr(GetModel()));
	
	// Draw the container (using container's vertex attributes)
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

glm::mat4 Cube::GetModel() const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position + m_OffsetPosition);
	model = glm::scale(model, m_Scale);

	return model;
}