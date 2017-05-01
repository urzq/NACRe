#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CubePreRender.h"
#include "shader/Program.h"

CubePreRender::CubePreRender(const Program& program)
{
	m_LightColor	= program.GetUniformLocation("lightColor");
	m_LightPos		= program.GetUniformLocation("lightPos");
}

void CubePreRender::PreRender(const glm::vec3& lightPos, const glm::vec3& lighColor)
{
	glUniform3f(m_LightPos, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(m_LightColor, lighColor.x, lighColor.y, lighColor.z);
}