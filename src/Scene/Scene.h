#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include "SceneNode.h"

class Scene
{
public:
	Scene();

	virtual void Update(float dT);

private:
	std::vector<std::unique_ptr<SceneNode>> m_SceneNodes;
};

#endif