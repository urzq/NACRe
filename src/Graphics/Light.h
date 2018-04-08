#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram;

class Light
{
	friend class Renderer;

public:
	void SetParameters(const glm::vec3& lightPos, const glm::vec3& camPos, const glm::vec3& lightColor);

private:
	void ApplyParametersToShader(ShaderProgram* shaderProgram);

private:
	GLint m_LightColorLoc;
	GLint m_LightPosLoc;
	GLint m_ViewPosLoc;

	glm::vec3 m_LightPos;
	glm::vec3 m_CamPos;
	glm::vec3 m_LightColor;
};

#endif