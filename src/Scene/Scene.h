#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "SceneNode.h"
#include "Scene/WhiteCube.h"
#include "Scene/MinecraftCube.h"

class Scene
{
public:
	Scene();

	void Update(float dT, glm::vec3 cameraPosition);

private:
	void UpdateLight(float dT, glm::vec3 cameraPosition);

private:
	WhiteCube m_WhiteCube;
	MinecraftCube m_MinecraftCube;
	std::vector<std::unique_ptr<SceneNode>> m_SceneNodes;
};

#endif