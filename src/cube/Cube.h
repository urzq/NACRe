#ifndef __CUBE_H__
#define __CUBE_H__

#include <glm/glm.hpp>

class Program;

class Cube
{
public:
	Cube(const Program& program, float initTime);
	
	void Update(float dT);
	void Render(const glm::mat4& projection, const glm::mat4& view);

	void SetPosition(const glm::vec3& position);
	void SetColor(const glm::vec3& color);

private:
	glm::mat4 GetModel() const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_OffsetPosition;
	glm::vec3 m_ObjectColor;

	GLuint m_ObjectColorLoc;
	GLuint m_ModelLoc;
	GLuint m_ViewLoc;
	GLuint m_ProjLoc;

	float m_TotalTime;
};

#endif