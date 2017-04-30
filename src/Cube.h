#ifndef __CUBE_H__
#define __CUBE_H__

#include <glm/glm.hpp>

class Program;

class Cube
{
public:
	Cube(const Program& program, float initTime);
	
	void Update(float dT);
	void Render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& lightPos);

	void SetPosition(glm::vec3& position);

private:
	glm::mat4 GetModel() const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_OffsetPosition;

	GLuint m_ObjectColor;
	GLuint m_LightColor;
	GLuint m_LightPos;
	GLuint m_Model;
	GLuint m_View;
	GLuint m_Proj;

	float m_TotalTime;
};

#endif