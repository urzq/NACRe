#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <vector>
#include <string>
#include <memory>

#include "Transform.h"

class VertexBuffer;
class ShaderProgram;
class GLTexture;

class Renderable
{
	friend class Renderer;

private:
	Renderable(std::shared_ptr<VertexBuffer> vertexBuffer, ShaderProgram* refShaderProgram, std::vector<GLTexture*> textures = {});

public:
	VertexBuffer* GetVertexBuffer();
	std::vector<GLTexture*>& GetTextures();
	ShaderProgram* GetShaderProgram();
	Transform& GetTransform();
	
	glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& color);

private:
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::vector<GLTexture*> m_Textures;
	ShaderProgram* m_RefShaderProgram;
	Transform m_Transform;

	glm::vec3 m_ObjectColor;
};

#endif