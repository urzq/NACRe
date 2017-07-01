#include "Light.h"
#include "shader/ShaderProgram.h"

void Light::SetParameters(const glm::vec3& lightPos, const glm::vec3& camPos, const glm::vec3& lightColor)
{
	m_LightPos = lightPos;
	m_CamPos = camPos;
	m_LightColor = lightColor;
}

void Light::ApplyParametersToShader(ShaderProgram* shaderProgram)
{
	// The uniform below might be equal to -1 (the shader doesnt have it).
	// In this case, glUniform3f does nothing.

	m_LightColorLoc = shaderProgram->GetUniformLocation("lightColor");
	glUniform3f(m_LightColorLoc, m_LightColor.x, m_LightColor.y, m_LightColor.z);

	m_LightPosLoc = shaderProgram->GetUniformLocation("lightPos");
	glUniform3f(m_LightPosLoc, m_LightPos.x, m_LightPos.y, m_LightPos.z);

	m_ViewPosLoc = shaderProgram->GetUniformLocation("viewPos");
	glUniform3f(m_ViewPosLoc, m_CamPos.x, m_CamPos.y, m_CamPos.z);
}