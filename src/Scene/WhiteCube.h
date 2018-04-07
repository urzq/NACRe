#ifndef __WHITE_CUBE_H__
#define __WHITE_CUBE_H__

#include <glm/glm.hpp>
#include "Core/Memory.h"

class Renderable;

class WhiteCube
{
public:
	WhiteCube();
	
	void SetPosition(const glm::vec3& startPosition);
	glm::vec3 GetPosition();
	glm::vec3 GetLightColor();

	void Update(float dT);

private:
	memory::unique_ptr_del<Renderable> m_Renderable;
	glm::vec3 m_LightColor;
	float m_TotalTime;
};

#endif