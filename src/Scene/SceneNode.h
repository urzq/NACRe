#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <glm/glm.hpp>

#include "Core/Memory.h"

class Renderable;

class SceneNode
{
public:
	SceneNode(const char* nodeName, const char* vertexBuferName);

	void SetPosition(const glm::vec3& position);
	void SceneNode::SetScale(const glm::vec3& scale);
	void SetColor(const glm::vec3& color);

	virtual void Update(float dT);

private:
	friend std::ostream& operator<<(std::ostream&, const SceneNode&);

private:
	memory::unique_ptr_del<Renderable> m_Renderable;
	const char* m_NodeName;

	// Keep track of the original position, so we can then apply an offset (=oscillation) on it.
	glm::vec3 m_originalPosition;
	// We apply sinus() to this total time, and it gives us an oscillation
	float m_totalTime;
	// The scene node does an oscillation on its y axis, going from -m_oscillationDistance to m_oscillationDistance
	float m_oscillationDistance;
};

#endif