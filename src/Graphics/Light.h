#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram;

class Light
{
	friend class Renderer;

public:
	Light();
	~Light();

	void SetParameters(const glm::vec3& lightPos, const glm::vec3& camPos, const glm::vec3& lightColor);

private:
	void SetShaderProgram(ShaderProgram* shaderProgram);

private:
	GLuint m_LightColorLoc;
	GLuint m_LightPosLoc;
	GLuint m_ViewPosLoc;

	glm::vec3 m_LightPos;
	glm::vec3 m_CamPos;
	glm::vec3 m_LightColor;

	ShaderProgram* m_ShaderProgram;
};

#endif