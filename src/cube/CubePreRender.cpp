#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CubePreRender.h"
#include "shader/Program.h"

CubePreRender::CubePreRender(const Program& program)
{
	m_LightColorLoc	= program.GetUniformLocation("lightColor");
	m_LightPosLoc = program.GetUniformLocation("lightPos");
	m_ViewPosLoc = program.GetUniformLocation("viewPos");

}

void CubePreRender::PreRender(const glm::vec3& lightPos, const glm::vec3& camPos, const glm::vec3& lighColor)
{
	glUniform3f(m_LightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(m_ViewPosLoc, camPos.x, camPos.y, camPos.z);
	glUniform3f(m_LightColorLoc, lighColor.x, lighColor.y, lighColor.z);
}