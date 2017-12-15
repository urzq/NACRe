#ifndef __MINECRAFT_CUBE_H__
#define __MINECRAFT_CUBE_H__

#include <glm/glm.hpp>
#include "Core/Memory.h"

class Renderable;

// TODO: it's a sprite for now, but make it a cube :)
class MinecraftCube
{
public:
	MinecraftCube();
	
	void SetPosition(const glm::vec3& startPosition);
	glm::vec3 GetPosition();

	void Update(float dT);

private:
	std::shared_ptr<VertexBuffer> CreateVertexBuffer();

private:
	Memory::unique_ptr_del<Renderable> m_Renderable;
};

#endif