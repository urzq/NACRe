#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>

class Program;

class Light
{
public:
	Light(int matrixID);
	
	void Update(float dT);
	void Render(const glm::mat4& projection, const glm::mat4& view);
	glm::vec3 GetPosition() const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	const float m_Radius;
	GLuint m_MatrixID;
	float m_TotalTime;
};

#endif