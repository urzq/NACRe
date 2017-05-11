#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glm/glm.hpp>

// Todo: see if there are better ways to handle this. Quaternions ?
class Transform
{
public:
	Transform();

	glm::vec3 GetPosition() const;
	void SetPosition(const glm::vec3& position);
	
	glm::vec3 GetEuler() const;
	void SetEuler(const glm::vec3& euler);

	glm::vec3 GetScale() const;
	void SetScale(const glm::vec3& scale);

	glm::mat4 GetMatrix() const;

private:
	glm::vec3 m_Position;
	glm::vec3 m_Euler;
	glm::vec3 m_Scale;
};

#endif