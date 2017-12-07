#ifndef __MINECRAFT_CUBE_H__
#define __MINECRAFT_CUBE_H__

#include <glm/glm.hpp>

class Renderable;

// TODO: it's a sprite for now, but make it a cube :)
class MinecraftCube
{
public:
	MinecraftCube();
	MinecraftCube(const MinecraftCube& other) = delete;
	MinecraftCube(MinecraftCube&& other) = delete;
	MinecraftCube& operator=(MinecraftCube&& other) = delete;
	~MinecraftCube();
	
	void SetPosition(const glm::vec3& startPosition);
	glm::vec3 GetPosition();

	void Update(float dT);

private:
	std::shared_ptr<VertexBuffer> CreateVertexBuffer();

private:
	Renderable* m_Renderable;
};

#endif