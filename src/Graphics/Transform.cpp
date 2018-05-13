#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "Transform.h"

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 mat = glm::translate(glm::mat4(1.0f), Position);
	mat = mat * glm::eulerAngleYXZ(Euler.y, Euler.x, Euler.z);
	mat = glm::scale(mat, Scale);

	return mat;
}