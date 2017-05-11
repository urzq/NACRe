#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <glm/glm.hpp>

class Renderable;

class SceneNode
{
public:
	SceneNode(const char* vertexBuferName);
	SceneNode(const SceneNode& other) = delete;
	SceneNode(SceneNode&& other);
	SceneNode& operator=(SceneNode&& other) = delete;
	~SceneNode();
	
	void SetPosition(const glm::vec3& position);
	void SetColor(const glm::vec3& color);

	virtual void Update(float dT);

private:
	Renderable* m_Renderable;
};

#endif