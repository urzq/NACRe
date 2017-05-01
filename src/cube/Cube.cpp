#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
#include "shader/Program.h"

Cube::Cube(const Program& program, float initTime):
	m_TotalTime(initTime),
	m_Position(0, 0, 0),
	m_Scale(0.7f),
	m_ObjectColor(1.0f, 1.0f, 0.3f)
{
	m_ObjectColorLoc = program.GetUniformLocation("objectColor");
	m_ModelLoc = program.GetUniformLocation("model");
	m_ViewLoc = program.GetUniformLocation("view");
	m_ProjLoc = program.GetUniformLocation("projection");
}

void Cube::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void Cube::SetColor(const glm::vec3& color)
{
	m_ObjectColor = color;
}

void Cube::Update(float dT)
{
	m_TotalTime += dT;
	m_OffsetPosition.z = sin(m_TotalTime);
}

void Cube::Render(const glm::mat4& projection, const glm::mat4& view)
{
	glUniform3f(m_ObjectColorLoc, m_ObjectColor.x, m_ObjectColor.y, m_ObjectColor.z);

	// Pass the matrices to the shader
	glUniformMatrix4fv(m_ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(m_ProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(m_ModelLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	
	// Draw the container (using container's vertex attributes)
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

glm::mat4 Cube::GetModel() const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position + m_OffsetPosition);
	model = glm::scale(model, m_Scale);

	return model;
}