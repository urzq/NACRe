#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <glm/glm.hpp>

#include "Core/Memory.h"

class Renderable;

class SceneNode
{
public:
	SceneNode(const char* vertexBuferName);

	void SetPosition(const glm::vec3& position);
	void SceneNode::SetScale(const glm::vec3& scale);
	void SetColor(const glm::vec3& color);

	virtual void Update(float dT);

private:
	memory::unique_ptr_del<Renderable> m_Renderable;
	const char* m_VertexBufferName;

	glm::vec3 glm_pos;
	glm::vec3 glm_scale = glm::vec3(1,1,1);
	glm::vec3 glm_euler;
	glm::vec3 glm_color;
};

#endif