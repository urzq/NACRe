#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <glm/glm.hpp>

class Renderable;

class SceneNode
{
public:
	SceneNode(const char* vertexBuferName);

	SceneNode(const SceneNode& other) = delete;
	SceneNode(SceneNode&& other) = delete;
	SceneNode& operator=(const SceneNode& other) = delete;
	SceneNode& operator=(SceneNode&& other) = delete;

	~SceneNode();
	
	void SetPosition(const glm::vec3& position);
	void SceneNode::SetScale(const glm::vec3& scale);
	void SetColor(const glm::vec3& color);

	virtual void Update(float dT);

private:
	Renderable* m_Renderable;
	const char* m_VertexBufferName;

	glm::vec3 glm_pos;
	glm::vec3 glm_scale = glm::vec3(1,1,1);
	glm::vec3 glm_euler;
	glm::vec3 glm_color;
};

#endif