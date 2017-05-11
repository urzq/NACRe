#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <string>
#include "Transform.h"

class VertexBuffer;
class ShaderProgram;

class Renderable
{
	friend class Renderer;

private:
	Renderable(const std::string& meshName, const std::string& vertexFilePath, const std::string& fragmentFilePath);
	Renderable(const Renderable& other) = delete;
	Renderable& operator=(const Renderable& other) = delete;
	Renderable(Renderable&& other) = delete;
	Renderable& operator=(Renderable&& other) = delete;
	~Renderable();

public:
	VertexBuffer* GetVertexBuffer();
	ShaderProgram* GetShaderProgram();
	Transform& GetTransform();
	
	glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& color);

private:
	VertexBuffer* m_VertexBuffer;
	ShaderProgram* m_ShaderProgram;
	Transform m_Transform;

	// TODO: create a polymorphic material class ? 
	glm::vec3 m_ObjectColor;
};

#endif