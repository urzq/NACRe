#ifndef __CUBE_H__
#define __CUBE_H__

#include <glm/glm.hpp>

class Renderable;

class Cube
{
public:
	Cube(float initTime);
	Cube(const Cube& other) = delete;
	Cube(Cube&& other);
	Cube& operator=(Cube&& other);
	~Cube();
	
	void SetStartPosition(const glm::vec3& startPosition);
	void SetColor(const glm::vec3& color);

	void Update(float dT);

private:
	Renderable* m_Renderable;

	glm::vec3 m_StartPosition;
	glm::vec3 m_OffsetPosition;

	float m_TotalTime;
};

#endif