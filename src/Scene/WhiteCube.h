#ifndef __WHITE_CUBE_H__
#define __WHITE_CUBE_H__

#include <glm/glm.hpp>

class Renderable;

class WhiteCube
{
public:
	WhiteCube();
	WhiteCube(const WhiteCube& other) = delete;
	WhiteCube(WhiteCube&& other) = delete;
	WhiteCube& operator=(WhiteCube&& other) = delete;
	~WhiteCube();
	
	void SetPosition(const glm::vec3& startPosition);
	glm::vec3 GetPosition();
	glm::vec3 GetLightColor();

	void Update(float dT);

private:
	Renderable* m_Renderable;
	glm::vec3 m_LightColor;
	float m_TotalTime;
};

#endif