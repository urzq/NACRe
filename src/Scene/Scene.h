#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "SceneNode.h"
#include "Scene/WhiteCube.h"

class Scene
{
public:
	Scene();

	virtual void Update(float dT, glm::vec3 cameraPosition);

private:
	WhiteCube m_WhiteCube;
	std::vector<std::unique_ptr<SceneNode>> m_SceneNodes;
};

#endif