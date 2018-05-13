#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glm/glm.hpp>

class Transform
{
public:
	glm::mat4 GetMatrix() const;

	glm::vec3 Position = glm::vec3(0, 0, 0);;
	glm::vec3 Euler = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1, 1, 1);
};

#endif